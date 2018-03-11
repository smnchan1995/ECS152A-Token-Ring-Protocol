#ifndef EVENT_H
#define EVENT_H


class Event{
    private:
        double time;
	int host;
        char type;
    public:
        Event();
        Event(double t,int h, char c);
        //~Event();

        void setTime(double t);
        double getTime()const;

        void setHost(int h);
        int getHost()const;

        void setType(char t);
        char getType()const;
};

#endif // EVENT_H
