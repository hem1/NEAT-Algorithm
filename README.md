# NEAT-Algorithm
neuro evolutionary augmented topologies

ref: "Evolving Neural Networks through Augmenting Topologies" Kenneth O. Stanley and Risto Miikkulainen

An attempt to develop the AI to play the snake game.

Input to the snakes is layer of 13 neurons and output is a layer of 3 neurons (straight, right and left (not in that order)).
The 13 inputs are wall[3],food[5] and body[5]. Snake can see if it hits the wall in next n=5 moves in 3 directions. It can sense food in 5 different direction with the angle of view of 240 degrees. It can also sense its body in 5 direction as it sense food. '1' if it can sense something else '0'.
In the output layer only one nueron can be set to '1' at any time.

When te snake grows longer, the AI is defeated but if the length of the snake is kept constant, AI has no problem playing the game
