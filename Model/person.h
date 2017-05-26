#include <QtCore\QObject>

#pragma db object
class Person : public QObject
{
public:
	#pragma db id auto
	unsigned int id;

signals:
	void signal1();

private slots:
	void slot2();
};