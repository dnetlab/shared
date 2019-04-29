# shared
Flash MTD partitioned read-write Library

## Makefile For Openwrt
```Makefile
include $(TOPDIR)/rules.mk

PKG_NAME:=shared
PKG_VERSION:=1.0

PKG_BUILD_DIR:= $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/dnetlab/shared.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=46e7d2ba461d186a16306dea254f0f996c68b254
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
    SECTION:=libs
    CATEGORY:=Dnetlab
    TITLE:=Library implementing the common function in embeded linux
endef

# define Build/Prepare
	# mkdir -p $(PKG_BUILD_DIR)
	# $(CP) ./src/* $(PKG_BUILD_DIR)/
# endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libshared.so $(1)/usr/lib/libshared.so
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libshared.so $(1)/usr/lib
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
```