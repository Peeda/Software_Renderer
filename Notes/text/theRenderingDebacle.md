This is in case the thing breaks later and I forgot what I did
# The Initial Solution
* At first the buffer was a 1d array of unsigned 32 int numbers, each in R8G8B8A8 formatting
* To read the data from the buffer and write to the screen I used the CPURender method which is still probably there,
it reads each u32 and extracts the RGBA values using bitwise shifts, then calls DrawPixel from raylib to draw that 
pixel to the screen, for each pixel in the buffer
* The issue with that is that it is extremely slow, which I found out after implementing rotations and only got 8 fps
* I had already tried to create a method that wrote the pixel data to a Raylib texture then drew that, but the colors 
weren't quite working so I initially decided to go with the CPURender method
# Fixing the texture rendering
* After realizing it wouldn't work I looked back into texture rendering, looking at this one reddit thread I saw they
used a byte array with each 4 indices representing one pixel and they had no issues with writing that to a texture
* I tried it and it worked, I was like what the hell, but I didn't want to use their thing
* The next 8 hours were spent reading byte data and trying to see if the Visual Studio c++ debugger could read C
* Eventually realized the issue is that for some reason when the buffer uses u32 the data is stored backwards in
comparison to when a byte array is used
* I had a fix that for each frame just reverses each u32 and writes it to a buffer of the Color struct defined in raylib
* 58 fps, I was thinking why not just use raylib color structs
* Alright then, I shall simply make the buffer use the Raylib Color data type, which is the same size
# The issue with that
* For some reason, the rendering looked mostly fine and the performance was great, but the grid background was super
glaringly sharp and distracting, the lines looked wider than before
* After messing around with the old and new versions, found that for some reason increasing the A value from 51 to
255 fixed it
* {51,51,51,51} -> {51,51,51,255};
* I was like what the hell, shouldn't that make the lines more defined
* The reason is because each frame, I was having raylib clear the canvas as white, then in one step the whole texture
was drawn to the screen
* Therefore the more opaque the pixels were, the more they revealed the white background, so the initial pixel data 
appeared as a stronger white, because it was transparent and revealing the white background which is {255,255,255,255};
* This issue probably already existed with the earlier implementation where it reverses the u32 data to a color, the 
difference was that before I probably just happened to use RGBA values with high A in the u32s, whereas when I changed 
the function calls around 
later I replaced it with a Color struct using lower A value, revealing the issue that was there the whole time
* Actually it must have existed the whole time, I just only noticed when refactoring so that functions with u32 parameters 
took colors

**The takeaway** is to not use opaque colors unless they are drawn after the texture is rendered, or else it just reveals
the white background
