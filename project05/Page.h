/**
 * @file Page.h
 * @brief The declaration of the page object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#ifndef PAGE_H
#define PAGE_H

/**
 * @brief The page object
 */
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
