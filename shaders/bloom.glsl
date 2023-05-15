// The original texture
uniform sampler2D referenceTex;

// The width and height of each pixel in texture coordinates
uniform float pixelWidth;
uniform float pixelHeight;

void mainImage(out vec4 pixel, in vec2 texel)
{
	
	// Larger constant = bigger glow
	float glow = 4.0 * ((pixelWidth + pixelHeight) / 2.0);
	
	// The vector to contain the new, "bloomed" colour values
	vec4 bloom = vec4(0);
	
	// Loop over all the pixels on the texture in the area given by the constant in glow
	int count = 0;
	for(float x = texel.x - glow; x < texel.x + glow; x += pixelWidth)
	{
		for(float y = texel.y - glow; y < texel.y + glow; y += pixelHeight)
		{
			// Add that pixel's value to the bloom vector
			// Add 1 to the number of pixels sampled
			count++;
		}
	}
	// Divide by the number of pixels sampled to average out the value
	// The constant being multiplied with count here will dim the bloom effect a bit, with higher values
	// Clamp the value between a 0.0 to 1.0 range
	bloom = clamp(bloom / (count * 30), 0.0, 1.0);
	
	// Set the current fragment to the original texture pixel, with our bloom value added on
	gl_FragColor = pixel + bloom;
}