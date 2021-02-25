#ifndef __EXPORTER_H__
#define __EXPORTER_H__

class Exporter{
    public:
        virtual void exportData() = 0;
};

class CSVexport : public Exporter {
    public:
        void exportData() override;
};

class JSONexport : public Exporter {
    public:
        void exportData() override;
};


#endif