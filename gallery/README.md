# Videos
[Demonstration video](https://youtu.be/uNnXn8bJfGM) shows the chess board startup and gameplay.

# Images
![Chess Board Final Picture](https://github.com/user-attachments/assets/00ea255e-7983-44ea-82a8-ce04d6561e1e)


## Public Engagement
This first image is at a chess club meeting, where a member asked to play against it and won! Previously, only my classmates and I had faced off against it and we always lost. The following weekend we brought it to a local chess tournament and had various participants face off against the board.
![Public Demonstration (First Winning Challenger)](https://github.com/user-attachments/assets/b2f9cda0-cb26-4556-830e-6903277978ee)


## Design Process
The first picture shows how we printed the board base and the squares. Each square was printed with wood Bambu Labs filament, and the base for themw as printed with black PLA Basic Bambu Labs filament. The base is mainly hollow so holes don't have to be redrilled for fitting the lights to the board. The pieces were glued to the base, and then glude together.
![Physical Assembly Process](https://github.com/user-attachments/assets/3f3a5985-1ee7-4960-a57e-145fd7e05ef5)

Each LED had to be wired separately, so four multiplexers had to be used. Each LED was small, and their wires were even smaller. Each of the 64 LEDs had to be routed and connected to both ground and power, leading to over 128 soldering points on the board. This wiring was completed in 4 sections, one for each corner of the board. The LEDs had to be mapped not just by their chess location, but also by their multiplexer adddress, as shown in the image.
![Chess Board Circuitry](https://github.com/user-attachments/assets/304976b0-bb12-419b-8975-fda69b65ca63)

## Light Brightness
The small LEDs proved to be very bright, and able to easily illuminate the moving location even in a well lit room.
![Light On Board](https://github.com/user-attachments/assets/d994a277-05d8-4e73-b46d-37666b1240ca)

The light shown through the pieces well as well, making gameplay easy to follow.
![Light Through Piece](https://github.com/user-attachments/assets/276c9a09-3d59-4acf-a4c6-60a5800250b8)

## Future developments
After finalizng the board, we realized that the LEDs would create an 8-bit display if we were able to light them quickly enough. The following picture shows multiple LEDs lit on the same multiplexer seemingly at once, although they are alternating so quickly that it looks as though each is lit individually. This shows future work could be done to enhance the board even further to display movements or text.
![Multiple Lights Demonstration](https://github.com/user-attachments/assets/f7370e52-a57a-40e8-91bc-5e88e6bf727b)
