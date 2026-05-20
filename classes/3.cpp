#include <iostream>

class log {

    public:
        const int loglevelwarning = 1;
        const int loglevelerror = 0;
        const int loglevelinfo = 2;

    private:
        int m_loglevel = loglevelinfo;

    public:
        void setlevel(int level) {
            m_loglevel = level;

        }

        void warn(const char* str) {
            if ( m_loglevel >= loglevelwarning ) {
                std::cout<<"[Warning]"<<str<<std::endl;
            }
        }
        void error(const char* str) {
            if ( m_loglevel >= loglevelerror ) {
                std::cout<<"[ERROR]"<<str<<std::endl;
            }
        }
        void info(const char* str) {
            if ( m_loglevel >= loglevelwarning) {
                std::cout<<"[INFO]"<<str<<std::endl;
            }
        }
};

int main() {
    log l;

    l.setlevel(l.loglevelinfo);
    l.warn("hello");
    l.error("oh no!");
}
