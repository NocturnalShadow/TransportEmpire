#include "Model/City.h"

City::City(const QJsonObject& city)
    : placeID           { city["place_id"].toString() },
      formatedAddress   { city["formatted_address"].toString() },
      location          { city["loction"].toObject() }
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
    city["location"]            = location.toJsonObject();
    return city;
}

