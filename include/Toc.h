#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Packet.hpp"

#define ACCESS_TYPE_BYTE 64
#define FLOAT_PARAM_TYPE 0x06

typedef std::pair<std::string, std::string> StrPair;

#pragma pack(push, 1)
struct FP16
{
    uint8_t _sign : 1;
    uint8_t _exponent : 5;
    uint16_t _value : 10;
};
#pragma pack(pop)

union ParamValue
{
    float _floatVal;
    float _FP16val;

    double _doubleVal;

    uint8_t _uint8Val;
    uint16_t _uint16Val;
    uint32_t _uintVal;
    uint64_t _uint64Val;

    int8_t _int8Val;
    int16_t _int16Val;
    int32_t _int32Val;
    int64_t _int64Val;
};

const std::map<uint8_t, std::string>
    PARAM_TYPES = {
        //   TypeId:       TypeName:
        {0x08, "uint8_t"},
        {0x09, "uint16_t"},
        {0x0A, "uint32_t"},
        {0x0B, "uint64_t"},
        {0x00, "int8_t"},
        {0x01, "int16_t"},
        {0x02, "int32_t"},
        {0x03, "int64_t"},
        {0x05, "FP16"},
        {0x06, "float"},
        {0x07, "double"}};

struct AccessType
{
    uint8_t _accessType;
    static const uint8_t RW;
    static const uint8_t RO;
    friend std::string to_string(AccessType const &self);
    AccessType &operator=(const std::string &strAccessType);
    AccessType &operator=(const uint8_t &accessType);
};

struct TocItemType
{
    uint8_t _type;
    operator std::string() const;
    friend std::string to_string(TocItemType const &self);
    bool operator==(uint8_t val) const;
    bool operator==(const std::string& val) const;
    TocItemType &operator=(const std::string &strParamType);
    TocItemType &operator=(const uint8_t &paramType);
};

struct TocItem
{
    std::string _groupName;
    std::string _name;
    TocItemType _type;
    AccessType _accessType;
    uint16_t _id;

    bool operator>(const TocItem &other) const;
    bool operator<(const TocItem &other) const;
    TocItem(const TocItem& other);
    TocItem(const bitcraze::crazyflieLinkCpp::Packet &p_recv);
    TocItem();
    ~TocItem();
    friend std::ostream &operator<<(std::ostream &out, const TocItem &tocItem);
};

struct TocInfo
{
    uint16_t _numberOfElements;
    uint32_t _crc;
    TocInfo();
    TocInfo(const bitcraze::crazyflieLinkCpp::Packet &p_recv);
    ~TocInfo();
    friend std::ostream &operator<<(std::ostream &out, const TocInfo &tocInfo);
};

class Toc
{
private:
    std::map<StrPair, TocItem> _tocItems;
    std::map<StrPair, TocItem> _tocItemsCache;
    TocInfo _tocInfo;

public:
    void insert(const TocItem &tocItem);
    TocItem getItem(const std::string &groupName, const std::string &paramName, bool caching = true) const;
    uint16_t getItemId(const std::string &groupName, const std::string &paramName, bool caching = true) const;
    std::vector<TocItem> getAllTocItems() const;
    std::vector<TocItem> getAllCachedTocItems() const;
    void clearCache();
    void clearToc();
};
