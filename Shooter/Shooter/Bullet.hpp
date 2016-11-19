//
//  Bullet.hpp
//  Shooter
//
//  Created by Hagar Yasser Omar on 11/19/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Trajectory.hpp"

class Bullet : public Trajectory{
public:
    Bullet();
    void draw();
};

#endif /* Bullet_hpp */
