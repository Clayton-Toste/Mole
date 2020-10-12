#pragma once

class MoleApp;

class Object
{
protected:
    Object (MoleApp * const app) : app{app} {};
public:
    MoleApp * const app;
};