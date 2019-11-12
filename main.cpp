#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include "main.h"


using namespace sf;

sf::Texture stick50, objYeetTex, stickJump, obstacleTex;
sf::Sprite player, objYeet, obstacle;
const int ground = 452;

int main() {

	RenderWindow window(VideoMode(800, 600), "The Yeeter"); // Create the window.


	stick50.loadFromFile("Stickman.png");
	stickJump.loadFromFile("stickmanJump.png");
	objYeetTex.loadFromFile("objYeetTex.png");
	objYeet.setTexture(objYeetTex);
	obstacleTex.loadFromFile("obstacleTex.png");
	obstacle.setTexture(obstacleTex);
	float playerX, playerY;
	playerX = 0;
	playerY = ground;
	float speed = 1;
	int obstacleX = 0;
	
	player.setTexture(stick50);

	//Clock clock;
	//float lastTime = 0;
	bool jump = false;
	bool reset = false;
	bool failed = false;
	bool goingUp = false;
	bool firstRun =  true;
	bool goingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool restrictDisp = false;
	

	while (window.isOpen()) {
		if (firstRun == true) {
			while ((!(obstacleX > playerX) || obstacleX >= 700)) {
				obstacleX = std::rand();
			}
			obstacle.setPosition(obstacleX, 575);
			firstRun = false;
		}
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up)) {
					playerY -= speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (playerY < ground)
						playerY += speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					movingLeft = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					movingRight = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Pause))
				{
					// Reset jump-related flags:
					jump = goingUp = goingDown = false; // Set all flags for jumping to false

					// Reset player:
					playerX = 0; // Resets player's X-coordinate on the window
					playerY = ground; // Resets player's X-coordinate on the window
					player.setTexture(stick50); // Sets player's texture to the one used when not jumping
					
					firstRun = true;
					obstacleX = 0;
					// Reset window:
					window.clear(Color(255, 255, 0)); // We will use yellow because if seen, we will know that we reset the game.
					window.display(); // Now we update the window and (maybe) show the yellow-colored window. NOTE: If you blink, you WILL miss it, it's that fast. Seriously.
				}
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					jump = true; // Set jump flag to true.
					goingUp = true; // When we jump, we will always gain a little height, (sometimes not much, but still). This flag should be self-explainatory.
				}
					
			}
			else if (e.type == Event::KeyReleased)
			{
				if (e.key.code == Keyboard::Left)
				{
					movingLeft = false;
				} else if (e.key.code == Keyboard::Right)
				{
					movingRight = false;
				}
			}
		}

		
		if (((obstacleX <= playerX) || (obstacleX <= (playerX + 72)))
		&& ((obstacleX + 25 >= playerX) || ((obstacleX + 25) >= (playerX + 72)))) {
			failed = true;
		}	
	
		

		// ========= Move ========= MOVE ========= Move ========= MOVE =========
		if (movingLeft == true) {
			if (playerX > 0)
				playerX -= speed;
		}
		else if (movingRight == true) {
			if (playerX < 728)
				playerX += speed;
		}

		// ========= JUMP ========= JUMP ========= JUMP ========= JUMP =========
		
		if (jump == true) {
			// Do jump function in here
			if (goingUp == true) {
				if (playerY <= ground - 150) {
					goingDown = true;
					goingUp = false;
				}
				else
					playerY -= 0.6*2;
			}
			else if (goingDown == true) {
				if (playerY >= ground) {
					goingDown = false;
					jump = false;
				}
				else
					playerY += 0.7*3;
			}
			player.setTexture(stickJump);
		// End the jump function
		}
		else {
			player.setTexture(stick50);
		}



		// ========= WINDOW DRAW ========= WINDOW DRAW ========= WINDOW DRAW

		player.setPosition(playerX, playerY); // Set player's position
		
		if (failed == false) {
			window.clear(Color(255, 255, 255)); // Clear window with a white background
			window.draw(player); // Draw player onto the screen
			window.draw(obstacle);
			window.display(); // Display the newly prepared screen. This is when everything becomes visible.
		}
	}
}