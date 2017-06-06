#ifndef SETFILTER_H
#define SETFILTER_H

#include<set>
#include<string>
#include <algorithm>

template<typename T, typename S = std::less<T> >
class set_filtering {
private:
    std::set<T, S>& mainset;
    std::set<T, S> filtered;
    S sorter;

public:
    set_filtering(std::set<T, S>& default_set) : mainset(default_set) {
        sorter = S();
    };

    ~set_filtering() {
        for(typename std::set<T, S>::iterator it = filtered.begin(); it != filtered.end();) {
            T elm = *it;
            mainset.insert(elm);
            filtered.erase(it++);
        }
    }

    void filter(T filt) {
        /*typename std::set<T, S>::iterator it = std::find(mainset.begin(), mainset.end(), filt);
        if (it != mainset.end()) {
            T elm = *it;
            filtered.insert(elm);
            mainset.erase(it);
        }*/
        typename std::set<T, S>::iterator it = mainset.find(filt);
        if (it != mainset.end()) {
            T elm = *it;
            filtered.insert(elm);
            mainset.erase(it);
        }
        /*for(typename std::set<T, S>::iterator it = mainset.begin(); it != mainset.end();) {
            T elm = *it;
            //if (elm == filt) {
            if (!sorter(elm, filt) && !sorter(filt, elm)) {
                filtered.insert(elm);
                mainset.erase(it++);
            } else {
                it++;
            }
        }*/
    }
    void unfilter(T filt) {
        /*typename std::set<T, S>::iterator it = std::find(filtered.begin(), filtered.end(), filt);
        if (it != filtered.end()) {
            T elm = *it;
            mainset.insert(elm);
            filtered.erase(it);
        }*/
        for(typename std::set<T, S>::iterator it = filtered.begin(); it != filtered.end();) {
            T elm = *it;
            if (!sorter(elm, filt) && !sorter(filt, elm)) {
                mainset.insert(elm);
                filtered.erase(it++);
            } else {
                it++;
            }
        }
    }
    void inverse() {
        std::set<T, S> temp = filtered;
        filtered = mainset;
        mainset = temp;
    }

    void operator ~ () {
        std::set<T, S> temp = filtered;
        filtered = mainset;
        mainset = temp;
    }

    template<typename F>
    void operator += (F f) {
        for(typename std::set<T, S>::iterator it = mainset.begin(); it != mainset.end();) {
            T elm = *it;
            if (f(elm)) {
                filtered.insert(elm);
                mainset.erase(it++);
            } else {
                it++;
            }
        }
    }

    template<typename F>
    void operator -= (F f) {
        for(typename std::set<T, S>::iterator it = filtered.begin(); it != filtered.end();) {
            T elm = *it;
            if (f(elm)) {
                mainset.insert(elm);
                filtered.erase(it++);
            } else {
                it++;
            }
        }
    }
};

#endif // SETFILTER_H
