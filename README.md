
# theknightdawns

## information: 
an amazing game 

## methods:
* 2D graphics library: 
  - Language: Cpp (sfml)

## documentation
### file I/O
  Beautiful tool for jsons:
    https://github.com/nlohmann/json
  `brew tap nlohmann/json`
  `brew install nlohmann-json`

### rendering 
  view: center
  viewPort: topleft corner
  sprites: top left corner
  text: top left corner

  -- moral of the story: views are the only thing that need a center

## object instantiation
  saying 
  Player test;
  would run the initialization code for player (if it required no arguments);

### header gaurd files
  `#define HUD` will destroy
  `class HUD{}`
  because they have the same name!!!

  instead do 
  `#define HUD_H`

***************************************************************************************************
***************************************************************************************************
***************************************************************************************************
####TODO

## fix scary pointer not getting freed error!!!
"main(93672,0x10a4e85c0) malloc: *** error for object 0x3f800000: pointer being freed was not allocated
main(93672,0x10a4e85c0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    93672 abort      ./main"

## battle mode
    -- lots of stuff todo
    -- first of all what stats should they even have
    -- how does inventory play into it?
    -- i think questing should level up character base health etc
    -- in fight some actions could be
        -- summon minions
            -- chalkling circle
        -- shoot / cast magic spell
        -- build defenses
        -- go up and hit with sword

## fix up problems with sprites
  -- the process for importing a new sprite sheet needs to be WAYYYY easier 

  -- Handle different sized sprites
    -- not by making them werid sizes!! - my beautiful art :(
    -- centering is kinda hacky too though: stuff falls over the edge of tiles...

# add inventory

### make sure we aren't rendering stuff off screen!!
  - eh Cpp is fast, this isn't really a priority atm since worlds are at most like 16 (?) times the size of the view
  -- but later: "sure why not"

***************************************************************************************************
***************************************************************************************************
***************************************************************************************************

