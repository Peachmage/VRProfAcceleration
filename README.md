A Test assignment performed using GAS. Full assignment in Russian is in the root folder of the repository.

Core of this assignment is "Acceleration" ability which simply increases your character's movement speed. It is activated by taking a powerup orb. How does that work?
1) A powerup orb triggers its overlap event. It applies GE_AccelerationStacker GameplayEffect to the character which, in turn, grants an automatically activated (via overridden OnAvatarSet()) 
GameplayAbility: GA_Acceleration. This effect can stack and refreshes it's duration upon application. However, once the duration runs out, all stacks are lost.
2) Once the ability is granted, it changes character's movement speed (increasing it by certain percentage * 1, as there is only one stack at that time), and activates an ability task which 
triggers a speed changing function every time stack count changes for the initial effect.
3) When effect's duration runs out, the ability is revoked and cancelled automatically. EndAbility() is overridden - it clears all changes to character's movement speed.

This setup ensures I am able to showcase as many parts of GAS as possible (GameplayEffects, Abilities, AbilityTasks, SetByCaller modifiers, GrantedAbilities, etc.) while also not requiring 
extensive additional setup for permanent ability giving and 'always active' abilities waiting for me to trigger powerups or anything like that.

Powerup, effect and ability are subclassed in blueprints to let a designer change ability duration, acceleration multiplier and powerup respawn time.

Last part of this project is a wall which breaks only if touched by character with sufficient speed (also configurable in BP). 