#ifndef PAGE_H
#define PAGE_H

class Page
{
    public:
        Page();
        ~Page();

        bool isValid();
        void setDirtyBit(bool setValue);
        bool getDirtyBit();
        void setValidBit(bool setValue);

    private:
        bool _valid;
        bool _dirty;
        int _memLocation;
};



#endif /* end of include guard: PAGE_H */
