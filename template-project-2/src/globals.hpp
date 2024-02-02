#pragma once

//      \/ CUSTOMIZABLE \/
#define GRAVITY_ACCELERATION 2468			    // how fast to start pulling down
#define GRAVITY_MAX 750                         // how strong to pull down

// NOTE: PLAYER_JUMP_VELOCITY together with GRAVITY_ACCELERATION determines how high is the player's jump
#define PLAYER_STANDART_VELOCITY 500            // how fast the player moves to the left and right
#define PLAYER_JUMP_VELOCITY -750			    // how fast the player moves up while jumping
#define PLAYER_LADDER_CLIMBING_SPEED 300        // how fast the player will move vertically when cllimbing a ladder
#define PLAYER_IMMORTALITY_PERIOD 0				// in seconds for how long barrel collision will be ignored

#define BARREL_STANDART_VELOCITY 600			// how fast the barrels will move left and right	
#define BARREL_SPAWN_PERIOD 2					// in seconds how much time has to elapse for a new barrel to spawn
#define BARREL_MAXIMUM_AMOUT 4				    // the maximum amout of barrels that can exist at one time
#define BARREL_RANDOM_SPAWN false				// whether to spawn barrels randomly on the top of the screen or use given coordinates

#define PRINT_CURSOR_CORDS_TOP_LEFT	false		// whether to print cursor coordinates in the top left corner of the screen (usefull for level creation)
#define PRINT_CURSOS_CORDS_NEXT_TO_CURSOR false // whether to print cursor cooridnates next to the cursor (usefull for level creation)
//      /\ CUSTOMIZABLE /\

// Note: Controls
// right arrow - move right
// left arrow - move left
// up arrow - climb ladder up when one is accesible
// down arrow - climb ladder down when one is accesible
// space - when on ground jump, when on ladder let go of ladder
// escape - close the program
// n - new game

// don't change
#define PRINT_CURSOR_CORDS PRINT_CURSOR_CORDS_TOP_LEFT || PRINT_CURSOS_CORDS_NEXT_TO_CURSOR

#define SCREEN_WIDTH 1000 // pixels
#define SCREEN_HEIGHT 750 // pixels

#define LADDER_SPRITE_HEIGHT 11 // pixels
#define LADDER_SPRITE_WIDTH 23 // pixels

#define PLATFORM_SPRITE_HEIGHT 23 // pixels
#define PLATFORM_SPRITE_WIDTH 23 // pixels

#define BARREL_SPRITE_WIDTH 35 // pixels
#define BARREL_SPRITE_HEIGHT 35 // pixels

#define PLAYER_SPRITE_HEIGHT 47 // pixels
#define PLAYER_SPRITE_WIDTH 35 // pixels