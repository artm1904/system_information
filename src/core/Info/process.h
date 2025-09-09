#pragma once

#include "../Utils/file_util.h"
#include "../core_global.h"

class CORE_EXPORT Process {
   public:
    Process();

    pid_t GetPid() const;
    void SetPid(pid_t value);

    quint64 GetRss() const;
    void SetRss(quint64 value);

    double GetPmem() const;
    void SetPmem(double value);

    quint64 GetVsize() const;
    void SetVsize(quint64 value);

    QString GetUname() const;
    void SetUname(const QString& value);

    double GetPcpu() const;
    void SetPcpu(double value);

    QString GetStartTime() const;
    void SetStartTime(const QString& value);

    QString GetState() const;
    void SetState(const QString& value);

    QString GetGroup() const;
    void SetGroup(const QString& value);

    int GetNice() const;
    void SetNice(int value);

    QString GetCpuTime() const;
    void SetCpuTime(const QString& value);

    QString GetSession() const;
    void SetSession(const QString& value);

    QString GetSeat() const;
    void SetSeat(const QString& value);

    QString GetCmd() const;
    void SetCmd(const QString& value);

   private:
    /**
     * @brief Идентификатор процесса (PID).
     */
    pid_t m_pid;
    /**
     * @brief Resident Set Size (RSS) - объем физической памяти, занимаемый процессом (в
     * килобайтах).
     */
    quint64 m_rss;
    /**
     * @brief Процент использования физической памяти процессом.
     */
    double m_pmem;
    /**
     * @brief Объем виртуальной памяти, используемый процессом (в килобайтах).
     */
    quint64 m_vsize;
    /**
     * @brief Имя пользователя, от которого запущен процесс.
     */
    QString m_uname;
    /**
     * @brief Процент использования процессорного времени.
     */
    double m_pcpu;
    /**
     * @brief Время запуска процесса.
     */
    QString m_startTime;
    /**
     * @brief Текущее состояние процесса (например, 'R' - Running, 'S' - Sleeping).
     */
    QString m_state;
    /**
     * @brief Группа, к которой принадлежит процесс.
     */
    QString m_group;
    /**
     * @brief Значение "nice" - приоритет планирования процесса.
     */
    int m_nice;
    /**
     * @brief Суммарное процессорное время, использованное процессом.
     */
    QString m_cpuTime;
    /**
     * @brief Идентификатор сессии процесса.
     */
    QString m_session;
    /**
     * @brief Идентификатор "seat" (физического рабочего места), с которым связан процесс.
     */
    QString m_seat;
    /**
     * @brief Команда, с помощью которой был запущен процесс.
     */
    QString m_cmd;
};