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
        int getTime()const;

        void setServiceTime(int l);
         int getServiceTime()const;

        void setType(char t);
         char getType()const;
};

#endif // EVENT_H
