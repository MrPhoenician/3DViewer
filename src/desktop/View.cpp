#include "View.h"

#include <QTimer>
#include <iostream>

using namespace s21;

Widget::Widget(QWidget *parent)
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

void Widget::resizeGL(int w, int h) { gl.glViewport(0, 0, w, h); }

bool Widget::saveScreenshot(const QString &filename) {
  QImage image = grabFramebuffer();
  image.scaled(640, 480, Qt::KeepAspectRatio);
  return image.save(filename);
}

Widget::~Widget() {
  if (timer) {
    killTimer(timer);
  }
}

MainWindow::MainWindow(Controller *contr, QWidget *parent)
    : QMainWindow(parent),
      controller(contr),
      openGL(OpenGL::getInstance()),
      projection('O') {
  GifTimer = new QTimer(this);
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
  // Создаем вертикальную компоновку для правой панели
  auto *rightPanelLayout = new QVBoxLayout;
  rightPanelLayout->setAlignment(Qt::AlignTop);
  rightPanelLayout->addWidget(buttonLoad);
  rightPanelLayout->addWidget(buttonSave);
  rightPanelLayout->addWidget(buttonGif);
  rightPanelLayout->addWidget(LModelName);
  rightPanelLayout->addWidget(LValueModelName);
  rightPanelLayout->addWidget(LVertices);
  rightPanelLayout->addWidget(LValueVertices);
  rightPanelLayout->addWidget(LEdges);
  rightPanelLayout->addWidget(LValueEdges);
  LValueModelName->setAlignment(Qt::AlignCenter);
  LValueVertices->setAlignment(Qt::AlignCenter);
  LValueEdges->setAlignment(Qt::AlignCenter);
  rightPanelLayout->addWidget(LTranslation);
  auto *sliderTXLayout = new QHBoxLayout;
  sliderTXLayout->addWidget(sliderTX);
  sliderTXLayout->addWidget(lineEditTX);
  rightPanelLayout->addLayout(sliderTXLayout);
  auto *sliderTYLayout = new QHBoxLayout;
  sliderTYLayout->addWidget(sliderTY);
  sliderTYLayout->addWidget(lineEditTY);
  rightPanelLayout->addLayout(sliderTYLayout);
  auto *sliderTZLayout = new QHBoxLayout;
  sliderTZLayout->addWidget(sliderTZ);
  sliderTZLayout->addWidget(lineEditTZ);
  rightPanelLayout->addLayout(sliderTZLayout);
  rightPanelLayout->addWidget(LRotation);
  auto *sliderRXLayout = new QHBoxLayout;
  sliderRXLayout->addWidget(sliderRotX);
  sliderRXLayout->addWidget(lineEditRX);
  rightPanelLayout->addLayout(sliderRXLayout);
  auto *sliderRYLayout = new QHBoxLayout;
  sliderRYLayout->addWidget(sliderRotY);
  sliderRYLayout->addWidget(lineEditRY);
  rightPanelLayout->addLayout(sliderRYLayout);
  auto *sliderRZLayout = new QHBoxLayout;
  sliderRZLayout->addWidget(sliderRotZ);
  sliderRZLayout->addWidget(lineEditRZ);
  rightPanelLayout->addLayout(sliderRZLayout);
  rightPanelLayout->addWidget(LScale);
  auto *sliderSLayout = new QHBoxLayout;
  sliderSLayout->addWidget(sliderScale);
  sliderSLayout->addWidget(lineEditS);
  rightPanelLayout->addLayout(sliderSLayout);
  rightPanelLayout->addWidget(buttonEdgeColor);
  rightPanelLayout->addWidget(buttonBackColor);
  rightPanelLayout->addWidget(buttonPointColor);
  rightPanelLayout->addWidget(toggleStipple);
  rightPanelLayout->addWidget(LThikness);
  rightPanelLayout->addWidget(sliderThikness);
  rightPanelLayout->addWidget(toggleRoundV);
  rightPanelLayout->addWidget(LPointSize);
  rightPanelLayout->addWidget(sliderVertices);
  rightPanelLayout->addWidget(projectionType);
  // Создаем контейнер для правой панели и устанавливаем фиксированную ширину
  auto *rightPanel = new QWidget(this);
  rightPanel->setLayout(rightPanelLayout);
  rightPanel->setFixedWidth(200);  // Фиксируем ширину правой панели
  // Создаем горизонтальную компоновку для всего окна
  auto *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(openGLWidget);  // Добавляем OpenGL-виджет с весом 2
  mainLayout->addWidget(rightPanel);
  auto *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);
}

void MainWindow::createWidgets() {
  openGLWidget = new Widget(this);
  buttonLoad = new QPushButton("Load model", this);
  buttonSave = new QPushButton("Save image", this);
  buttonEdgeColor = new QPushButton("Line color", this);
  buttonBackColor = new QPushButton("Background color", this);
  buttonPointColor = new QPushButton("Point color", this);
  buttonGif = new QPushButton("Make gif", this);
  LTranslation = new QLabel("Translation (X, Y, Z)", this);
  LRotation = new QLabel("Rotation (X, Y, Z)", this);
  LScale = new QLabel("Scale", this);
  LThikness = new QLabel("Line thikness", this);
  LPointSize = new QLabel("Vertice size", this);
  LModelName = new QLabel("Model name:", this);
  LValueModelName = new QLabel(this);
  LVertices = new QLabel("Number of vertices:", this);
  LValueVertices = new QLabel(this);
  LEdges = new QLabel("Number of edges:", this);
  LValueEdges = new QLabel(this);
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

void MainWindow::setNameAndValues(ObjData tempData) {
  LValueModelName->setText(QString::fromStdString(tempData.getName()));
  LValueVertices->setText(QString::number(tempData.getVerticesCount()));
  LValueEdges->setText(QString::number(tempData.getEdgesCount()));
}

void MainWindow::setupSliderSync(QSlider *slider, QLineEdit *lineEdit, int min,
                                 int max) {
  lineEdit->setText(QString::number(slider->value()));
  connect(slider, &QSlider::valueChanged, this,
          [lineEdit](int value) { lineEdit->setText(QString::number(value)); });
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

QLineEdit *MainWindow::createLineEdit(int charWidth) {
  QLineEdit *lineEdit = new QLineEdit(this);
  QFontMetrics fm(lineEdit->font());  // Получаем метрики шрифта
  int width = fm.horizontalAdvance(
      QString("0").repeated(charWidth));  // Ширина для charWidth символов
  lineEdit->setFixedWidth(width + 10);  // Добавляем немного запаса
  lineEdit->setAlignment(Qt::AlignCenter);  // Центрируем текст
  return lineEdit;
}

QSlider *MainWindow::createSliderWithLineEdit(int const min, int const max,
                                              int const average,
                                              QLineEdit **lineEditPtr) {
  auto *slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(min, max);
  slider->setValue(average);

  if (lineEditPtr) {
    *lineEditPtr = createLineEdit(3);
    setupSliderSync(slider, *lineEditPtr, min, max);
  }

  return slider;
}

void MainWindow::setupSliderConnects(QSlider *slider, Signal signal,
                                     char type) {
  connect(slider, &QSlider::valueChanged, this,
          [this, signal, type](int value) {
            if (type == 'T' && signal == AXIS_Z && projection == 'P') {
              data.setTranslate(value - 100, signal);
            } else if (type == 'T') {
              data.setTranslate(value, signal);
            } else {
              data.setRotate(value, signal);
            }
            openGL.setMatrix(controller->signal(data));
          });
}

void MainWindow::setupConnections() {
  connect(GifTimer, &QTimer::timeout, this, &MainWindow::makeGifLoop);
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
  connect(sliderScale, &QSlider::valueChanged, this, [this](int value) {
    data.setScale(value);
    openGL.setMatrix(controller->signal(data));
  });
  connect(toggleStipple, &QCheckBox::stateChanged, this,
          [this](int state) { openGL.setStippleLine(state == Qt::Checked); });
  connect(buttonEdgeColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonEdgeColor, "Select Line Color"); });
  connect(buttonBackColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonBackColor, "Select Background Color"); });
  connect(buttonPointColor, &QPushButton::clicked, this,
          [this]() { setColor(*buttonPointColor, "Select Point Color"); });
  connect(sliderThikness, &QSlider::valueChanged, this,
          [this](int value) { openGL.changeThikness(value); });
  connect(sliderVertices, &QSlider::valueChanged, this,
          [this](int value) { openGL.changePointSize(value); });
  connect(toggleRoundV, &QCheckBox::stateChanged, this,
          [this](int state) { openGL.setRoundVertices(state == Qt::Checked); });
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
  QColor color = QColorDialog::getColor(
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
  bool brightness =
      ((color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000) <
      128;  // Если яркость меньше 128, цвет считается темным
  button->setStyleSheet(QString("background-color: %1; color: %2;")
                            .arg(color.name())
                            .arg(brightness ? "white" : "black"));
}

void MainWindow::setButtonSave() {
  QFileDialog FileDialog;
  QString selectedFilter;
  QString FileName = FileDialog.getSaveFileName(
      this, tr("Save"), "", "BMP (*.bmp);; JPEG (*.jpg *.jpeg)",
      &selectedFilter);
  if (!FileName.isEmpty()) {
    if (!FileName.endsWith(".bmp", Qt::CaseInsensitive) &&
        !FileName.endsWith(".jpg", Qt::CaseInsensitive)) {
      selectedFilter == "BMP (*.bmp)" ? FileName += ".bmp" : FileName += ".jpg";
    }
    printf("%s", FileName.toStdString().c_str());
    if (!openGLWidget->saveScreenshot(FileName)) {
      QString Message =
          QString("Не удалось сохранить файл:  ").append(FileName);
      QMessageBox::warning(this, tr("Ошибка"), Message.toStdString().c_str());
    }
  }
}

void MainWindow::setProjection(const QString &text) {
  glm::mat4 projectionMat;
  if (text == "Orthographic") {
    projectionMat = controller->signal(0, true);
    data.setTranslate(sliderTZ->value(), 2);
    projection = 'O';
  } else if (text == "Perspective") {
    float aspect = static_cast<float>(width()) / height();
    projectionMat = controller->signal(aspect, false);
    data.setTranslate(sliderTZ->value() - 100, 2);
    projection = 'P';
  }
  openGL.setProjectionMat(projectionMat);
  openGL.setMatrix(controller->signal(data));
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
  QColor bColor = settings->value("backgroundColor", 0).value<QColor>();
  openGL.setBackgroundColor(bColor);
  updateButtonColor(buttonBackColor, bColor);
  QColor lColor = settings->value("lineColor", 0).value<QColor>();
  openGL.setLineColor(lColor);
  updateButtonColor(buttonEdgeColor, lColor);
  QColor pColor = settings->value("pointColor", 0).value<QColor>();
  openGL.setPointColor(pColor);
  updateButtonColor(buttonPointColor, pColor);
  projectionType->setCurrentText(
      settings->value("projectionType", 0).toString());
  toggleRoundV->setChecked(settings->value("round", 0).toBool());
  toggleStipple->setChecked(settings->value("stipple", 0).toBool());
}

void MainWindow::saveSettings() {
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
  if (GifTimer && GifTimer->isActive()) {
    GifTimer->stop();
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
    ObjData tempData = controller->signal(filePath->toStdString());
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
  QImage frame =
      openGLWidget->grabFramebuffer().scaled(640, 480, Qt::KeepAspectRatio);

  // Сохраняем кадр на диск
  QString fileName =
      QString("./ForGifFrame_%1.bmp").arg(GifId, 4, 10, QChar('0'));
  frame.save(fileName);
  GifId++;

  // Проверяем, завершено ли время записи GIF
  if (TimeCounter.elapsed() >= 5000) {  // 5 секунд
    GifTimer->stop();
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
    GifId = 0;
    GifTimer->start(100);  // Интервал между кадрами: 100 мс
    TimeCounter.start();
    openGLWidget->gifCapture = true;
    buttonGif->setText("Stop recording");
  }
}

void MainWindow::stopGifCapture() {
  if (GifTimer->isActive()) {
    GifTimer->stop();
    openGLWidget->gifCapture = false;
    buttonGif->setText("Make gif");
  }
}

QtView::QtView(Controller *controller, int argc, char *argv)
    : controller(controller), argc(argc), argv(argv) {}

int QtView::startView() {
  QApplication app(argc, &argv);
  MainWindow window(controller);
  window.show();

  return app.exec();
}