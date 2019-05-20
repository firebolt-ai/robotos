from PyQt5.QtWidgets import QApplication, QLabel, QWidget, QPushButton, QVBoxLayout
app = QApplication([])
window = QWidget()
label = QLabel('Settings.app')
label.show()
window.setLayout(layout)
window,show()
app.exec_()