#ifndef PORTRANGE_H
#define PORTRANGE_H

#include <common/common_types.h>

#include "valuerange.h"

using port_t = quint16;

using portrange_map_t = QMap<port_t, port_t>;
using port_arr_t = QVector<port_t>;

using PortPair = ValuePair<port_t>;

class PortRange : public ValueRange
{
    Q_OBJECT

public:
    explicit PortRange(QObject *parent = nullptr);

    bool isProtoTcp() const { return m_isProtoTcp; }
    void setProtoTcp(bool v) { m_isProtoTcp = v; }

    bool isProtoUdp() const { return m_isProtoUdp; }
    void setProtoUdp(bool v) { m_isProtoUdp = v; }

    const port_arr_t &portArray() const { return m_portArray; }
    port_arr_t &portArray() { return m_portArray; }

    const port_arr_t &pairFromArray() const { return m_pairFromArray; }
    port_arr_t &pairFromArray() { return m_pairFromArray; }

    const port_arr_t &pairToArray() const { return m_pairToArray; }
    port_arr_t &pairToArray() { return m_pairToArray; }

    int portSize() const { return m_portArray.size(); }
    int pairSize() const { return m_pairToArray.size(); }

    port_t portAt(int i) const { return m_portArray.at(i); }
    PortPair pairAt(int i) const { return PortPair { m_pairFromArray.at(i), m_pairToArray.at(i) }; }

    bool isEmpty() const override;

    bool checkSize() const override;
    int sizeToWrite() const override;

    void clear() override;

    void toList(QStringList &list) const override;

    bool fromList(const StringViewList &list, bool sort = true) override;

    void write(ConfData &confData) const override;

private:
    enum ParseError {
        ErrorOk = 0,
        ErrorBadFormat,
        ErrorBadRangeFormat,
        ErrorBadPort,
    };

    PortRange::ParseError parsePortLine(
            const QStringView line, portrange_map_t &portRangeMap, int &pairSize);

    PortRange::ParseError parsePortRange(const QStringView port, const QStringView port2,
            portrange_map_t &portRangeMap, int &pairSize);

    bool parsePortNumber(const QStringView port, port_t &v);

private:
    bool m_isProtoTcp : 1 = false;
    bool m_isProtoUdp : 1 = false;

    port_arr_t m_portArray;
    port_arr_t m_pairFromArray;
    port_arr_t m_pairToArray;
};

#endif // PORTRANGE_H
