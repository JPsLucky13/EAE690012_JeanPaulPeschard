Game Overview

The game is a 3D hack and slash game where the player can fire at enemies or slash them with their sword.

To open the game, go to the folder named Maps and double click SpawningCreepWaves.

Assignment03

To play the game, use W,A,S,D key to move around and the mouse to look around. Pressing 1 equips the assault rifle, pressing 2 equips the sword.
Press the left mouse button to active the equipped weapon.

Model

I placed data driven objects in a folder titled "Model", ui components for the enemies and player HUD are in a folder titled "View".
My things are the enemy types, the weapons and the player. The things are the win and lose conditions. The actions are fire machine gun, attack with
sword, spawn enemy, enemy move, enemy killed.
All other assets are in folders that correspond to their content.

Simulation

A player wins the game by killing 10 enemies within 100 seconds.
A player loses if the on screen counter reaches 0.

Unit Tests

I created 3 unit tests that are Unreal's functional tests. They run on a copy of the game map called FTEST_SpawningCreepWaves within the Test folder within the
Model folder. They are named FunctionalTest_EnemyDamage which tests the damage reduction of an enemy; FunctionalTest_EnemyEvade which tests the evation of an enemy;
FunctionalTest_EnemyHeal which tests the healing ability of an enemy.

To run the test, open the FTEST_SpawningCreepWaves map and go to Window->DeveloperTools->SessionFrontEnd. Hide and expand the "This Application" tab, then expand the 
"Automation" tab. In the "Automation" tab, expand Project->FunctionalTests and check the tests you wish to validate.
When done, click the "Start Tests" button and play. Press ESC to quit and see the log for the results of each test. 