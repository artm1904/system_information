#include "process.h"

Process::Process() {}

pid_t Process::GetPid() const { return m_pid; }

void Process::SetPid(pid_t value) { m_pid = value; }

quint64 Process::GetRss() const { return m_rss; }

void Process::SetRss(quint64 value) { m_rss = value; }

double Process::GetPmem() const { return m_pmem; }

void Process::SetPmem(double value) { m_pmem = value; }

quint64 Process::GetVsize() const { return m_vsize; }

void Process::SetVsize(quint64 value) { m_vsize = value; }

QString Process::GetUname() const { return m_uname; }

void Process::SetUname(const QString& value) { m_uname = value; }

double Process::GetPcpu() const { return m_pcpu; }

void Process::SetPcpu(double value) { m_pcpu = value; }

QString Process::GetStartTime() const { return m_startTime; }

void Process::SetStartTime(const QString& value) { m_startTime = value; }

QString Process::GetState() const { return m_state; }

void Process::SetState(const QString& value) { m_state = value; }

QString Process::GetGroup() const { return m_group; }

void Process::SetGroup(const QString& value) { m_group = value; }

int Process::GetNice() const { return m_nice; }

void Process::SetNice(int value) { m_nice = value; }

QString Process::GetCpuTime() const { return m_cpuTime; }

void Process::SetCpuTime(const QString& value) { m_cpuTime = value; }

QString Process::GetSession() const { return m_session; }

void Process::SetSession(const QString& value) { m_session = value; }

QString Process::GetSeat() const { return m_seat; }

void Process::SetSeat(const QString& value) { m_seat = value; }

QString Process::GetCmd() const { return m_cmd; }

void Process::SetCmd(const QString& value) { m_cmd = value; }