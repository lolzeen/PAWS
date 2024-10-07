#ifndef PAWS_LIB_DATASTORAGE_H
#define PAWS_LIB_DATASTORAGE_H
    #include "Config.h"

    class DataStorage {
        public:
            DataStorage();
            void init();
            uint32_t getData();
            void setData(uint32_t* setData);

        private:
            bool checkBuffer();
            void writeOnSD();
            
            
    };
#endif // PAWS_LIB_DATASTORAGE_H