/*
-----------------------------------------------------------------------------
Copyright (c) 26.02.2014 Tobias Peters <tobias.peters@kreativeffekt.at>

This file is part of Q-Gears

Q-Gears is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2.0 (GPLv2) of the License.

Q-Gears is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
-----------------------------------------------------------------------------
*/

#include <QDebug>

#include "data/c_archive_index.h"
#include "data/c_package.h"

using namespace wildstar;
using namespace wildstar::data;

int main(int argc, char *argv[])
{
    //CPackage file("D:/game/WildStar/Patch/ClientData.index");
    CArchiveIndex file("D:/game/WildStar/Patch/ClientData.index");

    try
    {
        file.open();
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
        return 1;
    }

    return 0;
}
