#include "Model/City.h"

City::City(const QJsonObject& city)
    : placeID           { city["place_id"].toString() },
      formatedAddress   { city["formatted_address"].toString() },
      location          { city["position"].toObject() }
{
}

City::City(const QString& _placeID, const QString& _formatedAddress, const Location& _location)
    : placeID           { _placeID },
      formatedAddress   { _formatedAddress },
      location          { _location }
{
}

QJsonObject City::toJsonObject() const
{
    QJsonObject city;
    city["place_id"]            = placeID;
    city["formatted_address"]   = formatedAddress;
    city["position"]            = location.toJsonObject();
    return city;
}

void City::update(Pointer<City> city){
    if(placeId != city->placeID){
        placeId = city->placeID;
    }
    if(formatedAddress != city->formatedAddress){
        formattedAddress = city->formatedAddress;
    }
    if(location.lat != city->location.lat){
        location.lat = city->location.lat;
    }
    if(location.lng != city->location.lng){
        location.lng = city->location.lng;
    }
}
