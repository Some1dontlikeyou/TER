#include "../include/Eleve.h"
int Eleve::id_count = 0;

Eleve::Eleve() : TransportTime(0), Transport(0), distance(0), flexibility(0)
{
    id_count+= 1;
    id = id_count;
}

Eleve::Eleve(int p_TransportTime, int p_Transport, int p_distance) : TransportTime(p_TransportTime), Transport(p_Transport), distance(p_distance), flexibility(0)
{
    id_count += 1;
    id = id_count;
}

Eleve::~Eleve()
{
    //dtor
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Eleve::descritpion(){
    cout<<"STUDENT "<<this->get_id()<<" : "<<endl;
    cout<<"Transport Time : "<<this->get_transportTime()<<endl;
    cout<<"transport : "<<this->get_transport()<<endl;
    cout<<"distance : "<<this->get_distance()<<endl;
    cout<<"flexibility : "<<this->get_flexibility()<<endl;
}