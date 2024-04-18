- [ ] Qt国际化方法。
- [x] 头像的动态替换
- [ ] bug:
  - TalkWindow 关闭后整个窗口都会关闭
  - 原因是有Qt有个close属性 当父控件为空，或者不为空但是不显示时 直接退出程序

- [ ] 解决办法 给他加了个父控件，但是if (testAttribute(Qt::WA_WState_ExplicitShowHide) && !testAttribute(Qt::WA_WState_Hidden))

  返回true， 导致子控件显示不出来。