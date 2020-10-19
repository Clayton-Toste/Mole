#pragma once

class RenderComponent
{
public:
    virtual const int render( ) const=0;
};

class UpdateComponent
{
public:
    virtual const int update( )=0;
};