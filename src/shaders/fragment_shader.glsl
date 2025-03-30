#version 330 core
out vec4 FragColor;
in float lineCoord;
uniform vec4 ourColor;
uniform int stippleLine;
uniform bool isCircle;  // Флаг для рисования круга

void main() {
  if (isCircle) {
    // Вычисляем расстояние от центра точки до текущего фрагмента
    vec2 coord =
        gl_PointCoord * 2.0 - 1.0;  // Переводим координаты в диапазон [-1, 1]
    float dist = length(coord);  // Расстояние от центра
    if (dist > 1.0) {
      discard;  // Отбрасываем фрагменты за пределами круга
    }
  }
  if (stippleLine == 1) {
    float pattern = mod(lineCoord * 50.0, 2.0);
    if (pattern > 0.5) discard;
  }
  FragColor = ourColor;
}