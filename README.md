# Простое устройство отключения водоснабжения в случае аварии с водой / Arduino

Простое устройство для перекрытия кранов при протечке воды, собранно на контроллере STM32. Собранно для личных целей, выложенно для интереса. Критика приветсвуется, но помните, я не являюсь профессиональным разработчиком.

В устройстве всего одна функциональная кнопка. Сделанно это осознано, для максимально простого управления без вникания: пищит - нажми, нет воды - нажми, хочешь закрыть краны - нажми, открыть - нажми, при этом всего одна и та же кнопка.

Устройство, на данный момент, при подключении питания становится в режим ожидания изменения сопротивления на датчиках. При срабатывании одного или нескольких датчиков, устройство по очередно закрывает краны, выводит на мини экран номера датчиков, противно пищит и больше не реагирует на изменения на датчиков.
Для отключения пронзительного писка, просто нажимаем кнопку. Повторное нажатие той же кнопки, заставит открыть краны один за другим. Но если датчики не высохли, то закроет краны снова.

При нажатии кнопки не в аварийном режими, заставит устройство открыть краны, если они закрыты или закрыть, если они открыты.

Внешний вид устройства:
<img src="files/IMG_20230620_155028.jpg" alt="Внешний вид платы" width="auto" height="auto" align="top">

Комплектация и ссылки для покупки элементов (основное):
1. [Программатор ST-Link](https://aliexpress.ru/item/32792513237.html?spm=a2g0o.order_list.order_list_main.611.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=10000015042616724)
2. [Кран DN15, DC5v, CR01](https://aliexpress.ru/item/32821745380.html?spm=a2g0o.order_list.order_list_main.551.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=64817703153)
3. [Драйвер двигателей L298N](https://aliexpress.ru/item/1005001621936295.html?spm=a2g0o.order_list.order_list_main.546.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000016846765674)
4. [Датчик воды простой](https://aliexpress.ru/item/1005002741992952.html?spm=a2g0o.order_list.order_list_main.541.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000021933922893)
5. [Кнопки с резиновой втулкой](https://aliexpress.ru/item/32673733924.html?spm=a2g0o.order_list.order_list_main.401.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=60207872197)
6. [Провод для протяжки датчиков](https://aliexpress.ru/item/1005001568848822.html?spm=a2g0o.order_list.order_list_main.11.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000030369248110)
7. [Клеймы](https://aliexpress.ru/item/1005003556955422.html?spm=a2g0o.order_list.order_list_main.76.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000026274837539)
8. [STM32F103C8T6](https://aliexpress.ru/item/1005003038641885.html?spm=a2g0o.order_list.order_list_main.141.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000023380646279)
9. [OLED экран SSD136](https://aliexpress.ru/item/1005004224962425.html?spm=a2g0o.order_list.order_list_main.136.5f1218029YgoDx&gatewayAdapt=glo2rus&sku_id=12000028455423552)
    
[Схема и исходники для easyeda](easyeda_com-water-shut-off.zip)


<img src="files/IMG_20230605_233239.jpg" alt="Разводка платы" width="auto" height="auto" align="top">

<img src="files/IMG_20230619_123218.jpg" alt="Размещение элементов" width="auto" height="auto" align="top">

Устройство было собранно под собственные нужды. Направлений к улучшению море. Можно сделать таймер тестового срабатывания от закисания кранов, в первой версии это было, но переписав не успел добавить. Радио датчики. Оповещение по телеграм. Автономное питание, хотя это по моему спорно. 

Небольшое видео работы устройства и мои колхозные рассуждения:
[![Watch the video](https://raw.githubusercontent.com/shliamb/water-shut-off/main/files/video.png)](https://www.youtube.com/embed/kJl_R9npxQE?si=utTMXmJ6Z3xOJjf_)






