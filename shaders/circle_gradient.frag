uniform vec2 u_resolution;

void main() {
    vec2 xy = gl_FragCoord.xy / u_resolution;
    gl_FragColor = vec4(xy.x, xy.y, (xy.x + xy.y) / 2.0, 1.0);
}