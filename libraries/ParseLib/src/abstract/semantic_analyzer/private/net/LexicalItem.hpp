// Copyright 2020, Lucas Sorenson, All rights reserved.


namespace sdg {

enum ItemType : int16_t
{
    Undefined,
    Header,
    Record,
    Value,
    Field
};

class LexicalItem
{
public:
    LexicalItem() = default;
    ~LexicalItem() = default;
    
private:
};

class LHeaderItem : public LexicalItem
{
public:
    LHeaderItem() = default;
    ~LHeaderItem() = default;
    
private:
    
};

class LRecordItem : public LexicalItem
{
public:
    LRecordItem() = default;
    ~LRecordItem() = default;
    
private:
    
};

class LValueItem : public LexicalItem
{
public:
    LValueItem() = default;
    ~LValueItem() = default;
    
private:
    
};

class LFieldItem : public LexicalItem
{
public:
    LFieldItem() = default;
    ~LFieldItem() = default;
    
private:
    
};

}// namespace sdg