#version 120
uniform sampler2D texture;
uniform sampler2D desktop;
uniform vec2 screenSize;
varying vec2 uvCoord;

vec4 sample_desktop(vec2 uv) {
	vec2 safe_uv = clamp(uv, vec2(0.002), vec2(0.998));
	return texture2D(desktop, vec2(safe_uv.x, -safe_uv.y));
}

vec4 blur_desktop(vec2 uv) {
	const int taps = 48;
	const float golden = 2.39996323;
	float radius = 12.0;
	vec2 texel = radius / screenSize;
	vec4 color = sample_desktop(uv);
	float total = 1.0;
	for (int i = 0; i < taps; i++) {
		float fi = float(i) + 0.5;
		float r = sqrt(fi / float(taps));
		float a = fi * golden;
		vec2 offset = vec2(cos(a), sin(a)) * r * texel;
		float w = exp(-r * r * 1.8);
		color += sample_desktop(uv + offset) * w;
		total += w;
	}
	return color / total;
}

void main() {
	vec4 selector = texture2D(texture, uvCoord);
	vec4 clear = sample_desktop(uvCoord);
	vec4 blurred = blur_desktop(uvCoord);
	vec3 dimmed = mix(clear.rgb, blurred.rgb, 0.74);
	dimmed = mix(dimmed, vec3(0.10, 0.12, 0.16), 0.10);
	vec4 outside = vec4(dimmed, 1.0);
	float mask = smoothstep(0.02, 0.10, selector.a);
	vec4 picked = mix(outside, clear, mask);
	gl_FragColor = vec4(mix(picked.rgb, selector.rgb, selector.a * 0.28), 1.0);
}
