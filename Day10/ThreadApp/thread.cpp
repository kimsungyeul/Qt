#include "thread.h"

Thread::Thread(QObject* obj) : m_stopFlag(Play){
    m_label = (QLabel*)obj;
}

void Thread::run() {
    Q_FOREVER{
        m_mutex.lock();
        if(m_stopFlag == Stop){
            m_waitCondition.wait(&m_mutex);
        }
        m_mutex.unlock();

        //m_label->setText(QString("run %1".arg(count++));      /* Non GUI 스레드 */
                                                                // 이렇게 직접적으로 접근하면 당연히 안됨
        emit setLabeled(QString("run %1").arg(count++));        // signal 선언후 emit으로 접근해야함
        sleep(1);
    }
}

void Thread::stopThread(){
    m_stopFlag = Stop;
}

void Thread::resumeThread(){
    m_mutex.lock();
    m_stopFlag = Play;
    m_waitCondition.wakeAll();
    m_mutex.unlock();
}
