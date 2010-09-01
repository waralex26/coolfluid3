#include <QSpinBox>
#include <QVariant>
#include <QVBoxLayout>

#include <climits>

#include "GUI/Client/GraphicalInt.hpp"

using namespace CF::GUI::Client;

GraphicalInt::GraphicalInt(bool isUint, QWidget * parent)
  : GraphicalValue(parent),
    m_isUint(isUint)
{
  m_spinBox = new QSpinBox(this);

  m_spinBox->setRange(m_isUint ? 0 : INT_MIN, INT_MAX);

  m_layout->addWidget(m_spinBox);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GraphicalInt::~GraphicalInt()
{
  delete m_spinBox;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool GraphicalInt::setValue(const QVariant & value)
{
  if(value.canConvert(m_isUint ? QVariant::UInt : QVariant::Int))
  {
    m_originalValue = value;
    m_spinBox->setValue(m_isUint ? value.toUInt() : value.toInt());
    return true;
  }

  return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QVariant GraphicalInt::getValue() const
{
  return m_spinBox->value();
}
