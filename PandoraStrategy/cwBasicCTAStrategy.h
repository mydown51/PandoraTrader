#pragma once
#include "cwBasicKindleStrategy.h"
#include "cwStrategyLog.h"
#include "cwSettlement.h"
#include "cwNetValueEvaluation.h"

//#define CW_NEED_STRATEGY_LOG

class cwBasicCTAStrategy
{
	//
public:
	struct cwCTAParaField
	{
		union
		{
			double			ParaList[50];
			struct
			{
				double		CTAPara1;
				double		CTAPara2;
				double		CTAPara3;
				double		CTAPara4;
				double		CTAPara5;
				double		CTAPara6;
				double		CTAPara7;
				double		CTAPara8;
				double		CTAPara9;
				double		CTAPara10;
				double		CTAPara11;
				double		CTAPara12;
				double		CTAPara13;
				double		CTAPara14;
				double		CTAPara15;
				double		CTAPara16;
				double		CTAPara17;
				double		CTAPara18;
				double		CTAPara19;
				double		CTAPara20;
				double		CTAPara21;
				double		CTAPara22;
				double		CTAPara23;
				double		CTAPara24;
				double		CTAPara25;
				double		CTAPara26;
				double		CTAPara27;
				double		CTAPara28;
				double		CTAPara29;
				double		CTAPara30;
				double		CTAPara31;
				double		CTAPara32;
				double		CTAPara33;
				double		CTAPara34;
				double		CTAPara35;
				double		CTAPara36;
				double		CTAPara37;
				double		CTAPara38;
				double		CTAPara39;
				double		CTAPara40;
				double		CTAPara41;
				double		CTAPara42;
				double		CTAPara43;
				double		CTAPara44;
				double		CTAPara45;
				double		CTAPara46;
				double		CTAPara47;
				double		CTAPara48;
				double		CTAPara49;
				double		CTAPara50;

			};
		};

	};

	struct TimeBalanceData
	{
		std::string		strDateTime;			//ʱ���ַ���
		std::uint64_t	iTimeStamp;				//ʱ���
		double			dBalance;				//��ӯ��
		double			dMaxFundOccupied;		//����ʽ�ռ��
		double			dNetAsset;				//��ֵ
	};
	typedef std::shared_ptr<TimeBalanceData> TimeBalanceDataPtr;


	struct EvaluatorTimeSeriesData
	{
		std::uint64_t	iTimeStamp;
		double			dNetAsset;					//��ֵ����
		double			dTradingYears;				//�ۼƽ������ޣ���Ȼ�ռ��㣩
		double          dIRR;						//�껯����
		double          dVolatility;				//�������ʵĲ�����
		double          dVolatilityDownward;		//���в�����
		double          dAR;						//�껯����

		double          dDrawDownRatio;				//��ǰ�س�����
		double          dMaxDrawDownRatio;			//���س���
		double          dAverageDDR;				//��ƽ���س���

		double          dSharpeRatio;				//���ձ���
		double          dSortinoRatio;				//����ŵ����
		double          dCalmarRatio;				//�������
		double          dSterlingRatio;				//˹���ֱ���
	};

public:
	cwBasicCTAStrategy(const char* szStrategyName);
	~cwBasicCTAStrategy();

	//��ʼ������
	virtual void			InitialStrategy() {};
	//������һ����K�ߵ�ʱ�򣬻���øûص�
	virtual void			OnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries) = 0;

	inline const char*		GetStrategyName() { return m_strStrategyName.c_str(); }

	void		 SetStrategyPosition(int iPosition, char * szInstrumentID = nullptr);
	int			 GetStrategyPosition(char* szInstrumentID = nullptr);

	double		 GetEntryPrice(std::string InstrumentID);
	size_t		 GetEntryIndex(std::string InstrumentID);
	const char * GetEntryTime(std::string InstrumentID);

	std::unordered_map<std::string,int>			m_iStrategyPositionMap;

	cwCTAParaField			m_StrategyPara;
	std::string				m_strDealInstrument;

	cwInstrumentDataPtr		m_pInstrument;
	//
	void					_PreOnBar(bool bFinished, int iTimeScale, cwBasicKindleStrategy::cwKindleSeriesPtr pKindleSeries);
	void                    UpdateEvaluator(double dCurrentMoneyUsed, double dCurrentTotalProfit,
											std::string str_time, std::uint64_t timeStamp, double dExpectedRet);

protected:
	std::string				m_strStrategyName;

#ifdef CW_NEED_STRATEGY_LOG
public:
	cwStrategyLog			m_StrategyLog;
#endif // CW_NEED_STRATEGY_LOG

private:
	cwStrategyLog			m_StrategyTradeListLog;

	//
	std::unordered_map<std::string, double>			m_dEntryPrice;
	std::unordered_map<std::string, size_t>			m_iEntryIndex;
	std::unordered_map<std::string, std::string>	m_strEntryTime;
public:
	double					m_dLastPrice;			//��ǰ�۸�
	size_t					m_iLastIndex;			//��ǰk����
	std::string				m_strLastUpdateTime;	//��ǰ����ʱ��

	//���ڼ�¼���Ծ�ֵ�仯
	cwSettlement									m_cwSettlement;
	std::deque<TimeBalanceDataPtr>					m_dTimeBalanceDQ;//����push back��������Ԫ��
	

	//����������
	cwNetValueEvaluation                            m_cwEvaluator;
	std::deque< EvaluatorTimeSeriesData>            m_dEvaluatorDQ;//�����������ݼ�¼
};
