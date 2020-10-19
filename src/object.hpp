#pragma once

class MoleApp;

class Object
{
protected:
    Object ( MoleApp * const app ) : app{app} { };
    MoleApp * const app;
public:
    virtual ~Object( ) { };
};