#ifndef EVENT_H
#define EVENT_H


class Event{
    private:
        int time, service_time;
        char type;
    public:
        Event();
        Event(int t,int l, char c);
        //~Event();

        void setTime(int t);
        const int getTime();

        void setServiceTime(int l);
        const int getServiceTime();

        void setType(char t);
        const char getType();
};

#endif // EVENT_H
