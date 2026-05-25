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
	float radius = 5.0;
	vec4 color = vec4(0.0);
	vec2 off1x = vec2(1.4117647 * radius, 0.0) / screenSize;
	vec2 off2x = vec2(3.2941176 * radius, 0.0) / screenSize;
	vec2 off3x = vec2(5.1764706 * radius, 0.0) / screenSize;
	vec2 off1y = vec2(0.0, 1.4117647 * radius) / screenSize;
	vec2 off2y = vec2(0.0, 3.2941176 * radius) / screenSize;
	vec2 off3y = vec2(0.0, 5.1764706 * radius) / screenSize;

	color += sample_desktop(uv) * 0.16;
	color += sample_desktop(uv + off1x) * 0.11;
	color += sample_desktop(uv - off1x) * 0.11;
	color += sample_desktop(uv + off2x) * 0.06;
	color += sample_desktop(uv - off2x) * 0.06;
	color += sample_desktop(uv + off3x) * 0.03;
	color += sample_desktop(uv - off3x) * 0.03;
	color += sample_desktop(uv + off1y) * 0.11;
	color += sample_desktop(uv - off1y) * 0.11;
	color += sample_desktop(uv + off2y) * 0.06;
	color += sample_desktop(uv - off2y) * 0.06;
	color += sample_desktop(uv + off3y) * 0.03;
	color += sample_desktop(uv - off3y) * 0.03;
	return color;
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
