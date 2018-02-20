#ifndef EVENT_H
#define EVENT_H


class Event{
    private:
        double time, service_time;
        char type;
    public:
        Event();
        Event(double t,double l, char c);
        //~Event();

        void setTime(double t);
        double getTime()const;

        void setServiceTime(double l);
        double getServiceTime()const;

        void setType(char t);
        char getType()const;
};

#endif // EVENT_H
