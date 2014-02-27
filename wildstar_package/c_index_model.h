#ifndef C_INDEX_MODEL_H
#define C_INDEX_MODEL_H

#include <QAbstractItemModel>

class CIndexModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CIndexModel(QObject *parent = 0);

signals:

public slots:

};

#endif // C_INDEX_MODEL_H
