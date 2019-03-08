#include "../include/Room.h"

int Room::id_count = 0;

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Room::Room() : type(0), capacity(0), location(0)
{
    id_count += 1;
    id = id_count;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Room::Room(int p_type, int p_capacity) : type(p_type), capacity(p_capacity), location(0){ //without location
    id_count += 1;
    id = id_count;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Room::Room(int p_type, int p_capacity, int p_location) : type(p_type), capacity(p_capacity), location(p_location){ //with location
    id_count += 1;
    id = id_count;
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
Room::~Room(){
}

///TESTS

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Room::test_capacity(int nb_etudiants){//test si la capacité est dépassée
    if (nb_etudiants > capacity)
        return false;
    return true;
}/** @brief (one liner)
  *
  * (documentation goes here)
  */

/** @brief (one liner)
  *
  * (documentation goes here)
  */
bool Room::is_same_id(const Room& p_room){//verifie que 2 id de salle soit differents
    if(p_room.id == id)
        return true;
    return false;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Room::descritpion(){
    cout<<"ROOM "<<this->get_id()<<" : "<<endl;
    cout<<"type : "<<this->get_type()<<endl;
    cout<<"capacity : "<<this->get_capacity()<<endl;
    cout<<"location : "<<this->get_location()<<endl;
}



