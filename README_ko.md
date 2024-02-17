[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP4725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp4725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MCP4725는 비휘발성 메모리(EEPROM)가 있는 저전력, 고정확도, 단일 채널, 12비트 버퍼 전압 출력 DAC(디지털-아날로그 변환기)입니다. 온보드 정밀 출력 증폭기를 통해 레일-투-레일 아날로그 출력 스윙을 달성할 수 있습니다.
DAC 입력 및 구성 데이터는 I2C 인터페이스 명령을 사용하여 사용자가 비휘발성 메모리(EEPROM)에 프로그래밍할 수 있습니다. 비휘발성 메모리 기능을 통해 DAC 장치는 전원이 꺼진 시간 동안 DAC 입력 코드를 유지할 수 있으며 전원이 켜진 직후 DAC 출력을 사용할 수 있습니다. 이 기능은 DAC 장치가 네트워크의 다른 장치에 대한 지원 장치로 사용될 때 매우 유용합니다. 이 장치에는 안정적인 전원 공급을 보장하는 POR(Power-On-Reset) 회로와 EEPROM 프로그래밍 전압을 위한 온보드 차지 펌프가 포함되어 있습니다. DAC 참조는 VDD에서 직접 구동됩니다. 전원이 꺼진 상태에서모드에서 출력 증폭기는 알려진 낮은, 중간 또는 높은 저항 출력 부하를 나타내도록 구성할 수 있습니다. MCP4725에는 외부 A0 주소 비트 선택 핀이 있습니다. 이 A0 핀은 사용자 애플리케이션 보드의 VDD 또는 VSS에 연결할 수 있습니다. MCP4725에는 2선 I2C가 있습니다. 표준(100kHz), 고속(400kHz) 또는 고속(3.4MHz) 모드용 호환 직렬 인터페이스. MCP4725는 설계 단순성과 작은 설치 공간이 필요한 이상적인 DAC 장치이며 전원이 꺼진 동안 DAC 장치 설정을 저장해야 하는 애플리케이션에 적합합니다. 이 장치는 소형 6핀 SOT-23 패키지로 제공됩니다. MCP4725는 센서 교정, 폐쇄 루프 서보 제어, 저전력 휴대용 기기, PC 주변기기 및 데이터 수집 시스템에 사용됩니다.

LibDriver MCP4725는 LibDriver에서 출시한 전체 기능 MCP4725 드라이버입니다. DAC 출력 및 DAC 출력 값 읽기 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver MCP4725의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver MCP4725용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver MCP4725드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver MCP4725프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver MCP4725오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 MCP4725데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

#### example basic

```C
#include "driver_mcp4725_basic.h"

uint8_t res;

res = mcp4725_basic_init(MCP4725_ADDR_A0_GND);
if (res != 0)
{
    return 1;
}

...

res = mcp4725_basic_write(1.2f);
if (res != 0)
{
    mcp4725_interface_debug_print("mcp4725: write failed.\n");
    (void)mcp4725_basic_deinit();

    ...
    
    return 1;
}

...

(void)mcp4725_basic_deinit();

return 0;
```

### 문서

온라인 문서: [https://www.libdriver.com/docs/mcp4725/index.html](https://www.libdriver.com/docs/mcp4725/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.