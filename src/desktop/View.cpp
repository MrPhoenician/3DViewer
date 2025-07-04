#include "View.h"

using namespace s21;

Widget::Widget(const QWidget *parent)
    : openGL(OpenGLFasad()), gl(InitOpenGL::getInstance()), isFile(false) {
  Q_UNUSED(parent);
  QSurfaceFormat format;
  //  format.setVersion(3, 3);  // Версия OpenGL 3.3
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setSwapInterval(1);  // Включаем вертикальную синхронизацию (VSync)
  setFormat(format);
  setGeometry(0, 0, 550, 670);
  setWindowTitle("3DViewer");
  timer = startTimer(DELAY);
}

void Widget::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  update();
}

void Widget::initializeGL() {
  gl.initialize();
  gl.glViewport(0, 0, width(), height());  // Устанавливаем область просмотра
  openGL.init();
}

void Widget::paintGL() {
  if (isFile) {
    openGL.draw();
  }
}

void Widget::resizeGL(const int w, const int h) { gl.glViewport(0, 0, w, h); }

bool Widget::saveScreenshot(const QString &filename) {
  const QImage image = grabFramebuffer();
  image.scaled(640, 480, Qt::KeepAspectRatio);
  return image.save(filename);
}

Widget::~Widget() {
  if (timer) {
    killTimer(timer);
  }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), openGL(OpenGL::getInstance()), projection('O') {
  gifTimer = new QTimer(this);
  createWidgets();
  createRightPanel();
  setupConnections();
  // Настройка размера окна
  resize(1000, 800);
  setWindowTitle("3DViewer 2.0 by Bellonar, Harkonex and Rafaelal");
  if (!settings->allKeys().isEmpty()) {
    QTimer::singleShot(0, this, &MainWindow::loadSettings);
  }
  openGLWidget->gifCapture = false;
}

void MainWindow::createRightPanel() {
  // Создаем контейнер для правой панели
  auto rightPanel = new QWidget(this);
  rightPanel->setFixedWidth(200);
  // Layout для правой панели, привязанный к rightPanel
  auto rightPanelLayout = new QVBoxLayout(rightPanel);
  rightPanelLayout->setAlignment(Qt::AlignTop);
  // Добавляем кнопки и метки
  rightPanelLayout->addWidget(buttonLoad);
  rightPanelLayout->addWidget(buttonSave);
  rightPanelLayout->addWidget(buttonGif);
  rightPanelLayout->addWidget(modelName);
  rightPanelLayout->addWidget(valueModelName);
  rightPanelLayout->addWidget(vertices);
  rightPanelLayout->addWidget(valueVertices);
  rightPanelLayout->addWidget(edges);
  rightPanelLayout->addWidget(valueEdges);
  valueModelName->setAlignment(Qt::AlignCenter);
  valueVertices->setAlignment(Qt::AlignCenter);
  valueEdges->setAlignment(Qt::AlignCenter);
  // Translation
  rightPanelLayout->addWidget(translation);
  auto sliderTXLayout = new QHBoxLayout();
  sliderTXLayout->addWidget(sliderTX);
  sliderTXLayout->addWidget(lineEditTX);
  rightPanelLayout->addLayout(sliderTXLayout);
  auto sliderTYLayout = new QHBoxLayout();
  sliderTYLayout->addWidget(sliderTY);
  sliderTYLayout->addWidget(lineEditTY);
  rightPanelLayout->addLayout(sliderTYLayout);
  auto sliderTZLayout = new QHBoxLayout();
  sliderTZLayout->addWidget(sliderTZ);
  sliderTZLayout->addWidget(lineEditTZ);
  rightPanelLayout->addLayout(sliderTZLayout);
  // Rotation
  rightPanelLayout->addWidget(rotation);
  auto sliderRXLayout = new QHBoxLayout();
  sliderRXLayout->addWidget(sliderRotX);
  sliderRXLayout->addWidget(lineEditRX);
  rightPanelLayout->addLayout(sliderRXLayout);
  auto sliderRYLayout = new QHBoxLayout();
  sliderRYLayout->addWidget(sliderRotY);
  sliderRYLayout->addWidget(lineEditRY);
  rightPanelLayout->addLayout(sliderRYLayout);
  auto sliderRZLayout = new QHBoxLayout();
  sliderRZLayout->addWidget(sliderRotZ);
  sliderRZLayout->addWidget(lineEditRZ);
  rightPanelLayout->addLayout(sliderRZLayout);
  // Scale
  rightPanelLayout->addWidget(scale);
  auto sliderSLayout = new QHBoxLayout();
  sliderSLayout->addWidget(sliderScale);
  sliderSLayout->addWidget(lineEditS);
  rightPanelLayout->addLayout(sliderSLayout);
  // Цвета и стили
  rightPanelLayout->addWidget(buttonEdgeColor);
  rightPanelLayout->addWidget(buttonBackColor);
  rightPanelLayout->addWidget(buttonPointColor);
  rightPanelLayout->addWidget(toggleStipple);
  rightPanelLayout->addWidget(thikness);
  rightPanelLayout->addWidget(sliderThikness);
  rightPanelLayout->addWidget(toggleRoundV);
  rightPanelLayout->addWidget(pointSize);
  rightPanelLayout->addWidget(sliderVertices);
  rightPanelLayout->addWidget(projectionType);
  // Устанавливаем layout на rightPanel
  rightPanel->setLayout(rightPanelLayout);
  // Центральный виджет приложения
  auto centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  // Основной layout: OpenGL + правая панель
  auto mainLayout = new QHBoxLayout(centralWidget);
  mainLayout->addWidget(openGLWidget);
  mainLayout->addWidget(rightPanel);
}

void MainWindow::createWidgets() {
  openGLWidget = new Widget(this);
  buttonLoad = new QPushButton("Load model", this);
  buttonSave = new QPushButton("Save image", this);
  buttonEdgeColor = new QPushButton("Line color", this);
  buttonBackColor = new QPushButton("Background color", this);
  buttonPointColor = new QPushButton("Vertice color", this);
  buttonGif = new QPushButton("Make gif", this);
  translation = new QLabel("Translation (X, Y, Z)", this);
  rotation = new QLabel("Rotation (X, Y, Z)", this);
  scale = new QLabel("Scale", this);
  thikness = new QLabel("Line thikness", this);
  pointSize = new QLabel("Vertice size", this);
  modelName = new QLabel("Model name:", this);
  valueModelName = new QLabel(this);
  vertices = new QLabel("Number of vertices:", this);
  valueVertices = new QLabel(this);
  edges = new QLabel("Number of edges:", this);
  valueEdges = new QLabel(this);
  toggleStipple = new QCheckBox("Stipple lines", this);
  toggleRoundV = new QCheckBox("Round vertices", this);
  sliderTX = createSliderWithLineEdit(0, 100, 50, &lineEditTX);
  sliderTY = createSliderWithLineEdit(0, 100, 50, &lineEditTY);
  sliderTZ = createSliderWithLineEdit(0, 100, 50, &lineEditTZ);
  sliderRotX = createSliderWithLineEdit(0, 360, 180, &lineEditRX);
  sliderRotY = createSliderWithLineEdit(0, 360, 180, &lineEditRY);
  sliderRotZ = createSliderWithLineEdit(0, 360, 180, &lineEditRZ);
  sliderScale = createSliderWithLineEdit(5, 200, 50, &lineEditS);
  sliderThikness = createSliderWithLineEdit(1, 10, 1, nullptr);
  sliderVertices = createSliderWithLineEdit(0, 15, 0, nullptr);
  projectionType = new QComboBox(this);
  projectionType->addItem("Orthographic");
  projectionType->addItem("Perspective");
  settings = new QSettings("S21", "3DViewer");
  filePath = new QString();
}

void MainWindow::setNameAndValues(ObjData tempData) const {
  valueModelName->setText(QString::fromStdString(tempData.getName()));
  valueVertices->setText(QString::number(tempData.getVerticesCount()));
  valueEdges->setText(QString::number(tempData.getEdgesCount()));
}

void MainWindow::setupSliderSync(QSlider *slider, QLineEdit *lineEdit, int min,
                                 int max) {
  lineEdit->setText(QString::number(slider->value()));
  connect(slider, &QSlider::valueChanged, this, [lineEdit](const int value) {
    lineEdit->setText(QString::number(value));
  });
  connect(lineEdit, &QLineEdit::editingFinished, this,
          [slider, lineEdit, min, max]() {
            bool ok;
            int value = lineEdit->text().toInt(&ok);
            if (ok && value >= min && value <= max) {
              slider->setValue(value);
            } else {
              lineEdit->setText(QString::number(slider->value()));
            }
          });
}

QLineEdit *MainWindow::createLineEdit(const int charWidth) {
  const auto lineEdit = new QLineEdit(this);
  const QFontMetrics fm(lineEdit->font());  // Получаем метрики шрифта
  const int width = fm.horizontalAdvance(
      QString("0").repeated(charWidth));  // Ширина для charWidth символов
  lineEdit->setFixedWidth(width + 10);  // Добавляем немного запаса
  lineEdit->setAlignment(Qt::AlignCenter);  // Центрируем текст
  return lineEdit;
}

QSlider *MainWindow::createSliderWithLineEdit(int const min, int const max,
                                              int const average,
                                              QLineEdit **lineEditPtr) {
  const auto slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(min, max);
  slider->setValue(average);

  if (lineEditPtr) {
    *lineEditPtr = createLineEdit(3);
    setupSliderSync(slider, *lineEditPtr, min, max);
  }

  return slider;
}

void MainWindow::setupSliderConnects(const QSlider *slider, Signal signal,
                                     char type) {
  connect(slider, &QSlider::valueChanged, this,
          [this, signal, type](const int value) {
            if (type == 'T' && signal == AXIS_Z && projection == 'P') {
              data.setTranslate(static_cast<float>(value) - 100, signal);
            } else if (type == 'T') {
              data.setTranslate(static_cast<float>(value), signal);
            } else {
              data.setRotate(static_cast<float>(value), signal);
            }
            openGL.setMatrix(Controller::signal(data));
          });
}

void MainWindow::setupConnections() {
  connect(gifTimer, &QTimer::timeout, this, &MainWindow::makeGifLoop);
  connect(projectionType, &QComboBox::currentTextChanged, this,
          [this](const QString &text) { setProjection(text); });
  connect(buttonLoad, &QPushButton::clicked, this, [this]() {
    *filePath =
        QFileDialog::getOpenFileName(this, "Load Model", "../data-samples",
                                     "OBJ Files (*.obj);;All Files (*)");
    loadObj();
  });
  connect(buttonSave, &QPushButton::clicked, this,
          [this]() { setButtonSave(); });
  connect(sliderScale, &QSlider::valueChanged, this, [this](const int value) {
    data.setScale(static_cast<float>(value));
    openGL.setMatrix(Controller::signal(data));
  });
  connect(
      toggleStipple, &QCheckBox::stateChanged, this,
      [this](const int state) { openGL.setStippleLine(state == Qt::Checked); });
  connect(buttonEdgeColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonEdgeColor, "Select Line Color"); });
  connect(buttonBackColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonBackColor, "Select Background Color"); });
  connect(buttonPointColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonPointColor, "Select Point Color"); });
  connect(sliderThikness, &QSlider::valueChanged, this,
          [this](const int value) { openGL.changeThikness(value); });
  connect(sliderVertices, &QSlider::valueChanged, this,
          [this](const int value) { openGL.changePointSize(value); });
  connect(toggleRoundV, &QCheckBox::stateChanged, this,
          [this](const int state) {
            openGL.setRoundVertices(state == Qt::Checked);
          });
  connect(buttonGif, &QPushButton::clicked, this, [this]() {
    !openGLWidget->gifCapture ? startGifCapture() : stopGifCapture();
  });
  setupSliderConnects(sliderTX, AXIS_X, 'T');
  setupSliderConnects(sliderTY, AXIS_Y, 'T');
  setupSliderConnects(sliderTZ, AXIS_Z, 'T');
  setupSliderConnects(sliderRotX, AXIS_X, 'R');
  setupSliderConnects(sliderRotY, AXIS_Y, 'R');
  setupSliderConnects(sliderRotZ, AXIS_Z, 'R');
}

void MainWindow::setColor(QPushButton &button, const QString &text) {
  const QColor color = QColorDialog::getColor(
      buttonEdgeColor->palette().button().color(), this, text);
  if (color.isValid()) {
    if (&button == buttonBackColor) {
      openGL.setBackgroundColor(color);
    } else if (&button == buttonPointColor) {
      openGL.setPointColor(color);
    } else {
      openGL.setLineColor(color);
    }
    updateButtonColor(&button, color);
  }
}

void MainWindow::updateButtonColor(QPushButton *button, const QColor &color) {
  const bool brightness =
      ((color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000) <
      128;  // Если яркость меньше 128, цвет считается темным
  const auto style =
      std::format("background-color: {}; color: {};",
                  color.name().toStdString(), brightness ? "white" : "black");
  button->setStyleSheet(QString::fromStdString(style));
}

void MainWindow::setButtonSave() {
  QString selectedFilter;
  QString FileName = QFileDialog::getSaveFileName(
      this, tr("Save"), "", "BMP (*.bmp);; JPEG (*.jpg *.jpeg)",
      &selectedFilter);
  if (!FileName.isEmpty()) {
    if (!FileName.endsWith(".bmp", Qt::CaseInsensitive) &&
        !FileName.endsWith(".jpg", Qt::CaseInsensitive)) {
      selectedFilter == "BMP (*.bmp)" ? FileName += ".bmp" : FileName += ".jpg";
    }
    printf("%s", FileName.toStdString().c_str());
    if (!openGLWidget->saveScreenshot(FileName)) {
      const QString Message =
          QString("Не удалось сохранить файл:  ").append(FileName);
      QMessageBox::warning(this, tr("Ошибка"), Message.toStdString().c_str());
    }
  }
}

void MainWindow::setProjection(const QString &text) {
  glm::mat4 projectionMat;
  if (text == "Orthographic") {
    projectionMat = Controller::signal(0, true);
    data.setTranslate(static_cast<float>(sliderTZ->value()), 2);
    projection = 'O';
  } else if (text == "Perspective") {
    const float aspect =
        static_cast<float>(width()) / static_cast<float>(height());
    projectionMat = Controller::signal(aspect, false);
    data.setTranslate(static_cast<float>(sliderTZ->value()) - 100, 2);
    projection = 'P';
  }
  openGL.setProjectionMat(projectionMat);
  openGL.setMatrix(Controller::signal(data));
}

void MainWindow::loadSettings() {
  int savedValue = settings->value("sliderTX", 0).toInt();
  sliderTX->setValue(savedValue);
  savedValue = settings->value("sliderTY", 0).toInt();
  sliderTY->setValue(savedValue);
  savedValue = settings->value("sliderTZ", 0).toInt();
  sliderTZ->setValue(savedValue);
  savedValue = settings->value("sliderRotX", 0).toInt();
  sliderRotX->setValue(savedValue);
  savedValue = settings->value("sliderRotY", 0).toInt();
  sliderRotY->setValue(savedValue);
  savedValue = settings->value("sliderRotZ", 0).toInt();
  sliderRotZ->setValue(savedValue);
  savedValue = settings->value("sliderScale", 0).toInt();
  sliderScale->setValue(savedValue);
  savedValue = settings->value("sliderThikness", 0).toInt();
  sliderThikness->setValue(savedValue);
  savedValue = settings->value("sliderVertices", 0).toInt();
  sliderVertices->setValue(savedValue);
  if (settings->contains("filePath") &&
      !settings->value("filePath").toString().isEmpty()) {
    *filePath = settings->value("filePath", 0).toString();
    loadObj();
  }
  auto bColor = settings->value("backgroundColor", 0).value<QColor>();
  openGL.setBackgroundColor(bColor);
  updateButtonColor(buttonBackColor, bColor);
  auto lColor = settings->value("lineColor", 0).value<QColor>();
  openGL.setLineColor(lColor);
  updateButtonColor(buttonEdgeColor, lColor);
  auto pColor = settings->value("pointColor", 0).value<QColor>();
  openGL.setPointColor(pColor);
  updateButtonColor(buttonPointColor, pColor);
  projectionType->setCurrentText(
      settings->value("projectionType", 0).toString());
  toggleRoundV->setChecked(settings->value("round", 0).toBool());
  toggleStipple->setChecked(settings->value("stipple", 0).toBool());
}

void MainWindow::saveSettings() const {
  settings->setValue("sliderTX", sliderTX->value());
  settings->setValue("sliderTY", sliderTY->value());
  settings->setValue("sliderTZ", sliderTZ->value());
  settings->setValue("sliderRotX", sliderRotX->value());
  settings->setValue("sliderRotY", sliderRotY->value());
  settings->setValue("sliderRotZ", sliderRotZ->value());
  settings->setValue("sliderScale", sliderScale->value());
  settings->setValue("sliderThikness", sliderThikness->value());
  settings->setValue("sliderVertices", sliderVertices->value());
  settings->setValue("filePath", *filePath);
  settings->setValue("backgroundColor", openGL.getBackgroundColor());
  settings->setValue("lineColor", openGL.getLineColor());
  settings->setValue("pointColor", openGL.getPointColor());
  settings->setValue("projectionType", projectionType->currentText());
  settings->setValue("round", toggleRoundV->isChecked());
  settings->setValue("stipple", toggleStipple->isChecked());
  settings->sync();
}

MainWindow::~MainWindow() {
  saveSettings();
  if (gifTimer && gifTimer->isActive()) {
    gifTimer->stop();
  }
  // Удаляем временные файлы GIF с помощью QFile
  QDir dir(".");
  dir.setNameFilters(QStringList() << "ForGifFrame_*.bmp");
  dir.setFilter(QDir::Files);
  for (const QString &file : dir.entryList()) {
    QFile::remove(file);
  }
}

void MainWindow::loadObj() {
  if (!filePath->isEmpty()) {
    openGLWidget->makeCurrent();  // включить openGL контекст
    ObjData tempData = Controller::signal(filePath->toStdString());
    if (tempData.getStatus()) {
      openGL.uploadDataToBuffers(tempData);
      setNameAndValues(tempData);
    } else {
      QMessageBox::critical(
          this, "Ошибка",
          "Невозможно прочитать данные из файла, попробуйте выбрать другой");
    }
    openGLWidget->isFile = true;
    openGLWidget->doneCurrent();
  }
}

void MainWindow::makeGifLoop() {
  // Захватываем текущий кадр
  const QImage frame =
      openGLWidget->grabFramebuffer().scaled(640, 480, Qt::KeepAspectRatio);

  // Сохраняем кадр на диск
  const QString fileName =
      QString("./ForGifFrame_%1.bmp").arg(gifId, 4, 10, QChar('0'));
  frame.save(fileName);
  gifId++;

  // Проверяем, завершено ли время записи GIF
  if (timeCounter.elapsed() >= 5000) {  // 5 секунд
    gifTimer->stop();
    openGLWidget->gifCapture = false;

    // Создаем GIF из сохраненных кадров с помощью QProcess
    QProcess process;
    QStringList arguments;
    arguments << "-delay" << "10" << "-loop" << "0" << "./ForGifFrame_*.bmp"
              << "animation.gif";
    process.start("convert", arguments);
    process.waitForFinished();

    if (process.exitCode() == 0) {
      QMessageBox::information(this, "SAVED AS GIF", "Скринкаст сохранён");

      // Удаляем временные файлы с помощью QFile
      QDir dir(".");
      dir.setNameFilters(QStringList() << "ForGifFrame_*.bmp");
      dir.setFilter(QDir::Files);
      for (const QString &file : dir.entryList()) {
        QFile::remove(file);  // Удаляем каждый файл
      }
    } else {
      QMessageBox::warning(
          this, tr("Ошибка"),
          tr("Не удалось создать GIF. Возможно, требуется установить утилиту "
             "convert: sudo apt install imagemagick"));
    }
    buttonGif->setText("Make gif");
  }
}

void MainWindow::startGifCapture() {
  if (!openGLWidget->gifCapture) {
    gifId = 0;
    gifTimer->start(100);  // Интервал между кадрами: 100 мс
    timeCounter.start();
    openGLWidget->gifCapture = true;
    buttonGif->setText("Stop recording");
  }
}

void MainWindow::stopGifCapture() const {
  if (gifTimer->isActive()) {
    gifTimer->stop();
    openGLWidget->gifCapture = false;
    buttonGif->setText("Make gif");
  }
}

QtView::QtView(const int argc, char *argv) : argc(argc), argv(argv) {}

int QtView::startView() {
  QApplication app(argc, &argv);
  MainWindow window;
  window.show();

  return QApplication::exec();
}