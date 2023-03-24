/* PageTransition.h
 * Copyright (C) 2005, Net Integration Technologies, Inc.
 * Copyright (C) 2005, Brad Hards <bradh@frogmouth.net>
 * Copyright (C) 2015, Arseniy Lartsev <arseniy@alumni.chalmers.se>
 * Copyright (C) 2018, 2021 Albert Astals Cid <aacid@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */
 
#ifndef __PAGETRANSITION_X_H__
#define __PAGETRANSITION_X_H__
 
#include "poppler-export.h"
 
#include <QtCore/qglobal.h>
 
namespace Poppler {
 
class PageTransitionParams;
class PageTransitionData;
 
class POPPLER_QT5_EXPORT PageTransition
{
public:
    // if changed remember to keep in sync with PageTransition.h enum
    enum Type
    {
        Replace = 0,
        Split,
        Blinds,
        Box,
        Wipe,
        Dissolve,
        Glitter,
        Fly,
        Push,
        Cover,
        Uncover,
        Fade
    };
 
    // if changed remember to keep in sync with PageTransition.h enum
    enum Alignment
    {
        Horizontal = 0,
        Vertical
    };
 
    // if changed remember to keep in sync with PageTransition.h enum
    enum Direction
    {
        Inward = 0,
        Outward
    };
 
    // TODO Next ABI break, make this private and remove reference
    explicit PageTransition(const PageTransitionParams &params);
 
    PageTransition(const PageTransition &pt);
 
    PageTransition &operator=(const PageTransition &other);
 
    ~PageTransition();
 
    Type type() const;
 
    Q_DECL_DEPRECATED int duration() const;
 
    double durationReal() const;
 
    Alignment alignment() const;
 
    Direction direction() const;
 
    int angle() const;
 
    double scale() const;
 
    bool isRectangular() const;
 
private:
    PageTransitionData *data;
};
 
}
 
#endif

