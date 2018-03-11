//Packet Header

#ifndef PACKET_H
#define PACKET_H


class Packet{
    private:
        int size, destination;
        double arrival_time;
    public:
        Packet();
        Packet(double t,int s, int d);
        //~Packet`();

        void setArrivalTime(double t);
        double getArrivalTime()const;

        void setSize(int s);
        int getSize()const;

        void setDestination(int d);
        int getDestination()const;
};

#endif // PACKET_H
