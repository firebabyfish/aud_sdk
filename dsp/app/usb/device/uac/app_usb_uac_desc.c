#include "app_usb_uac_desc.h"


#define APP_USB_UAC_USE_SPEAKER    0
#define APP_USB_UAC_USE_MICROPHONE 1

#if (APP_USB_UAC_USE_SPEAKER && APP_USB_UAC_USE_MICROPHONE)
#define APP_USB_UAC_DESCR_TOTAL_LEN 0xC2
#define APP_USB_UAC_INTERFACE_NUMS  3
#define APP_USB_UAC_AC_HEADER_LEN   0x0A
#define APP_USB_UAC_AC_TOTAL_LEN    0x48
#define APP_USB_UAC_IN_COLLECTION   0x02
#define APP_USB_UAC_INTERFACE_NR    0x01, 0x02
#elif (APP_USB_UAC_USE_SPEAKER && !APP_USB_UAC_USE_MICROPHONE)
#define APP_USB_UAC_DESCR_TOTAL_LEN 0x6E
#define APP_USB_UAC_INTERFACE_NUMS  2
#define APP_USB_UAC_AC_HEADER_LEN   0x09
#define APP_USB_UAC_AC_TOTAL_LEN    0x28
#define APP_USB_UAC_IN_COLLECTION   0x01
#define APP_USB_UAC_INTERFACE_NR    0x01
#elif (!APP_USB_UAC_USE_SPEAKER && APP_USB_UAC_USE_MICROPHONE)
#define APP_USB_UAC_DESCR_TOTAL_LEN 0x6E
#define APP_USB_UAC_INTERFACE_NUMS  2
#define APP_USB_UAC_AC_HEADER_LEN   0x09
#define APP_USB_UAC_AC_TOTAL_LEN    0x28
#define APP_USB_UAC_IN_COLLECTION   0x01
#define APP_USB_UAC_INTERFACE_NR    0x01
#endif


/* Device Descriptor */
const uint8_t uac_dev_descr[] = {
    0x12,                                               // bLength
    0x01,                                               // bDescriptorType (Device)
    0x10, 0x01,                                         // bcdUSB 1.10
    0x00,                                               // bDeviceClass
    0x00,                                               // bDeviceSubClass
    0x00,                                               // bDeviceProtocol
    DEF_USBD_UEP0_SIZE,                                 // bMaxPacketSize0 64
    (uint8_t)DEF_USB_VID, (uint8_t)(DEF_USB_VID >> 8),  // idVendor 0x1A86
    (uint8_t)DEF_USB_PID, (uint8_t)(DEF_USB_PID >> 8),  // idProduct 0x5537
    DEF_IC_PRG_VER, 0x00,                               // bcdDevice 0.01
    0x01,                                               // iManufacturer (String Index)
    0x02,                                               // iProduct (String Index)
    0x03,                                               // iSerialNumber (String Index)
    0x01,                                               // bNumConfigurations 1
};

/* Configuration Descriptor */
const uint8_t uac_cfg_descr[] = {
    // Configuration Descriptor
    0x09,                               // bLength
    0x02,                               // bDescriptorType (Configuration)
    APP_USB_UAC_DESCR_TOTAL_LEN, 0x00,  // wTotalLength (to be calculated based on the full length of the descriptors)
    APP_USB_UAC_INTERFACE_NUMS,         // bNumInterfaces (number of interfaces)
    0x01,                               // bConfigurationValue
    0x00,                               // iConfiguration
    0x80,                               // bmAttributes: Bus-powered; Remote wakeup
    0x32,                               // MaxPower: 100mA

#if 1 /* AC () */
    // Audio Control Interface Descriptor (Audio Control Interface)
    0x09,  // bLength
    0x04,  // bDescriptorType (Interface)
    0x00,  // bInterfaceNumber
    0x00,  // bAlternateSetting
    0x00,  // bNumEndpoints
    0x01,  // bInterfaceClass (Audio)
    0x01,  // bInterfaceSubClass (Audio Control)
    0x00,  // bInterfaceProtocol
    0x00,  // iInterface

    // Audio Control Interface Header Descriptor
    APP_USB_UAC_AC_HEADER_LEN,       // bLength
    0x24,                            // bDescriptorType (CS Interface)
    0x01,                            // bDescriptorSubtype (Header)
    0x00, 0x01,                      // bcdADC (Audio Device Class Specification Version)
    APP_USB_UAC_AC_TOTAL_LEN, 0x00,  // wTotalLength (Length of this descriptor plus all following descriptors in the control interface)
    APP_USB_UAC_IN_COLLECTION,       // bInCollection (Number of Audio Control Interfaces in this collection)
    APP_USB_UAC_INTERFACE_NR,        // baInterfaceNr[1] (Interface number of first audio control interface)
#endif

#if APP_USB_UAC_USE_SPEAKER
    /* Terminal (31) */
    // Input Terminal Descriptor
    0x0C,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x02,        // bDescriptorSubtype (Input Terminal)
    0x01,        // bTerminalID (ID for this terminal)
    0x01, 0x01,  // wTerminalType (USB Streaming)
    0x00,        // bAssocTerminal (No associated terminal)
    0x02,        // bNrChannels (Number of channels: 2 channels)
    0x03, 0x00,  // wChannelConfig (Left and Right channels)
    0x00,        // iChannelNames (No channel names)
    0x00,        // iTerminal (No terminal name)

    // Feature Unit Descriptor
    0x0A,  // bLength
    0x24,  // bDescriptorType (CS Interface)
    0x06,  // bDescriptorSubtype (Feature Unit)
    0x02,  // bUnitID (Feature Unit ID)
    0x01,  // bSourceID (Source Terminal ID)
    0x01,  // bControlSize (1 byte for controls)
    0x01,  // Mute Control on Master Channel
    0x02,  // Volume Control on Left Front channel
    0x02,  // Volume Control on Right Front channel
    0x00,  // iFeature (No feature string)

    // Output Terminal Descriptor
    0x09,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x03,        // bDescriptorSubtype (Output Terminal)
    0x03,        // bTerminalID (Output Terminal ID)
    0x02, 0x03,  // wTerminalType (Headphone)
    0x00,        // bAssocTerminal (No associated terminal)
    0x02,        // bSourceID (Source ID)
    0x00,        // iTerminal (No terminal string)

    /* Audio Streaming (52) */
    // Audio Streaming Interface Descriptor (Alternate Setting 0)
    0x09,  // bLength
    0x04,  // bDescriptorType (Interface)
    0x01,  // bInterfaceNumber (Audio Streaming Interface)
    0x00,  // bAlternateSetting (Alternate Setting 0)
    0x00,  // bNumEndpoints (No endpoints in this setting)
    0x01,  // bInterfaceClass (Audio)
    0x02,  // bInterfaceSubClass (Audio Streaming)
    0x00,  // bInterfaceProtocol
    0x00,  // iInterface (No interface string)

    // Audio Streaming Interface Descriptor (Alternate Setting 1)
    0x09,  // bLength
    0x04,  // bDescriptorType (Interface)
    0x01,  // bInterfaceNumber
    0x01,  // bAlternateSetting (Alternate Setting 1)
    0x01,  // bNumEndpoints (1 endpoint)
    0x01,  // bInterfaceClass (Audio)
    0x02,  // bInterfaceSubClass (Audio Streaming)
    0x00,  // bInterfaceProtocol
    0x00,  // iInterface (No interface string)

    // Audio Streaming General Descriptor
    0x07,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x01,        // bDescriptorSubtype (General)
    0x01,        // bTerminalLink (Link to terminal 1)
    0x01,        // bDelay (1 ms)
    0x01, 0x00,  // wFormatTag (PCM format)

    // Audio Streaming Format Type Descriptor
    0x0B,              // bLength
    0x24,              // bDescriptorType (CS Interface)
    0x02,              // bDescriptorSubtype (Format Type)
    0x01,              // bFormatType (Type I - PCM)
    0x02,              // bNrChannels (2 channels)
    0x02,              // bSubframeSize (2 bytes per frame)
    0x10,              // bBitResolution (16 bits per sample)
    0x01,              // bSamFreqType (1 frequency supported)
    0x80, 0xBB, 0x00,  // tSamFreq (48 kHz)

    // Audio Streaming Endpoint Descriptor (ISO Data Endpoint)
    0x09,        // bLength
    0x05,        // bDescriptorType (Endpoint)
    0x03,        // bEndpointAddress (OUT endpoint)
    0x09,        // bmAttributes (Isochronous)
    0xC0, 0x00,  // wMaxPacketSize (192 bytes)
    0x01,        // bInterval (1 frame)
    0x00,        // bRefresh
    0x00,        // bSynchAddress

    // Audio Streaming Endpoint Descriptor (General Audio)
    0x07,        // bLength
    0x25,        // bDescriptorType (CS Endpoint)
    0x01,        // bDescriptorSubtype (General)
    0x01,        // bmAttributes (Sampling Frequency Control)
    0x01,        // bLockDelayUnits
    0x01, 0x00,  // wLockDelay (1 ms)
#endif

#if APP_USB_UAC_USE_MICROPHONE
    /* Terminal (31) */
    // Input Terminal Descriptor
    0x0C,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x02,        // bDescriptorSubtype (Input Terminal)
    0x04,        // bTerminalID (ID for this terminal)
    0x01, 0x02,  // wTerminalType (Microphone)
    0x00,        // bAssocTerminal (No associated terminal)
    0x02,        // bNrChannels (Number of channels: 2 channels)
    0x03, 0x00,  // wChannelConfig (Left and Right channels)
    0x00,        // iChannelNames (No channel names)
    0x00,        // iTerminal (No terminal name)

    // Feature Unit Descriptor
    0x0A,  // bLength
    0x24,  // bDescriptorType (CS Interface)
    0x06,  // bDescriptorSubtype (Feature Unit)
    0x05,  // bUnitID (Feature Unit ID)
    0x04,  // bSourceID (Source Terminal ID)
    0x01,  // bControlSize (1 byte for controls)
    0x01,  // Mute Control on Master Channel
    0x00,  // Left Front channel
    0x00,  // Right Front channel
    0x00,  // iFeature (No feature string)

    // Output Terminal Descriptor
    0x09,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x03,        // bDescriptorSubtype (Output Terminal)
    0x06,        // bTerminalID (Output Terminal ID)
    0x01, 0x01,  // wTerminalType (USB Streaming Terminal Type)
    0x00,        // bAssocTerminal (No associated terminal)
    0x05,        // bSourceID (Source ID)
    0x00,        // iTerminal (No terminal string)

    /* Audio Streaming (52) */
    // Audio Streaming Interface Descriptor (Alternate Setting 0)
    0x09,  // bLength
    0x04,  // bDescriptorType (Interface)
    0x01,  // bInterfaceNumber (Audio Streaming Interface)
    0x00,  // bAlternateSetting (Alternate Setting 0)
    0x00,  // bNumEndpoints (No endpoints in this setting)
    0x01,  // bInterfaceClass (Audio)
    0x02,  // bInterfaceSubClass (Audio Streaming)
    0x00,  // bInterfaceProtocol
    0x00,  // iInterface (No interface string)

    // Audio Streaming Interface Descriptor (Alternate Setting 1)
    0x09,  // bLength
    0x04,  // bDescriptorType (Interface)
    0x01,  // bInterfaceNumber
    0x01,  // bAlternateSetting (Alternate Setting 1)
    0x01,  // bNumEndpoints (1 endpoint)
    0x01,  // bInterfaceClass (Audio)
    0x02,  // bInterfaceSubClass (Audio Streaming)
    0x00,  // bInterfaceProtocol
    0x00,  // iInterface (No interface string)

    // Audio Streaming General Descriptor
    0x07,        // bLength
    0x24,        // bDescriptorType (CS Interface)
    0x01,        // bDescriptorSubtype (General)
    0x06,        // bTerminalLink (Link to terminal 6)
    0x00,        // bDelay (0 ms)
    0x01, 0x00,  // wFormatTag (PCM format)

    // Audio Streaming Format Type Descriptor
    0x0B,              // bLength
    0x24,              // bDescriptorType (CS Interface)
    0x02,              // bDescriptorSubtype (Format Type)
    0x01,              // bFormatType (Type I - PCM)
    0x02,              // bNrChannels (2 channels)
    0x02,              // bSubframeSize (2 bytes per frame)
    0x10,              // bBitResolution (16 bits per sample)
    0x01,              // bSamFreqType (1 frequency supported)
    0x80, 0xBB, 0x00,  // tSamFreq (48 kHz)

    // Audio Streaming Endpoint Descriptor (ISO Data Endpoint)
    0x09,        // bLength
    0x05,        // bDescriptorType (Endpoint)
    0x83,        // bEndpointAddress (IN endpoint)
    0x0D,        // bmAttributes (Isochronous)
    0xC0, 0x00,  // wMaxPacketSize (192 bytes)
    0x01,        // bInterval (1 frame)
    0x00,        // bRefresh
    0x00,        // bSynchAddress

    // Audio Streaming Endpoint Descriptor (General Audio)
    0x07,        // bLength
    0x25,        // bDescriptorType (CS Endpoint)
    0x01,        // bDescriptorSubtype (General)
    0x00,        // bmAttributes
    0x01,        // bLockDelayUnits
    0x01, 0x00,  // wLockDelay (1 ms)
#endif
};

/* Language Descriptor */
const uint8_t uac_lang_descr[] = {
    0x04, 0x03, 0x09, 0x04};

/* Manufacturer Descriptor */
const uint8_t uac_manu_info[] = {
    0x10, 0x03, 'C', 0, 's', 0, 'q', 0, 'u', 0, 'a', 0, 'r', 0, 'e'};

/* Product Information */
const uint8_t uac_prod_info[] = {
    0x24, 0x03,
    'C', 0,
    'S', 0,
    ' ', 0,
    'G', 0,
    'a', 0,
    'm', 0,
    'i', 0,
    'n', 0,
    'g', 0,
    ' ', 0,
    'H', 0,
    'e', 0,
    'a', 0,
    'd', 0,
    's', 0,
    'e', 0,
    't', 0};

/* Serial Number Information */
const uint8_t uac_serial_info[] = {
    0x16, 0x03, '0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0, '9', 0};
