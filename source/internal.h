#ifndef INTERNAL
#define INTERNAL

typedef struct
{
	bool m_systemSelected;
	int m_systemId;
	QString m_selectedSystemName;

	bool m_stationSelected;
	int m_stationId;
	QString m_stationName;

	bool m_commoditySelected;
	int m_commodityId;
} SSTATE, *PSSTATE;

#endif // INTERNAL

