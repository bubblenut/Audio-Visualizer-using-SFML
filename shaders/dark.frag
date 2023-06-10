void main() {
    vec4 newColor = gl_FragColor;
    newColor.a = 0.5;
    gl_FragColor = newColor;
}