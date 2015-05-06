# shell脚本创建1000个表

### 场景： 

* 用shell脚本建立1000个表，表名为record_000, record_001, ... record_999

### 方法1：

* table.sql如下

```sql
DROP TABLE IF EXISTS `record_???`;
CREATE TABLE `record_???` (
    `recordId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    `supporterUserType` tinyint(1) unsigned NOT NULL,
    `supporterUserId` bigint(20) unsigned NOT NULL,
    `supporterOpenId` varchar(64) NOT NULL,
    `starterUserType` tinyint(1) unsigned NOT NULL,
    `starterUserId` bigint(20) unsigned NOT NULL,
    `starterOpenId` varchar(64) NOT NULL,
    `businessId` tinyint(3) unsigned NOT NULL,
    `activityId` bigint(20) unsigned NOT NULL,
    `commodityId` varchar(64) NOT NULL,
    `supportTime` int(11) unsigned NOT NULL,
    `supportType` tinyint(1) unsigned NOT NULL,
    `recvRedPackTime` int(11) unsigned NOT NULL,
    `redPackId` varchar(64) NOT NULL,
    `lastUpdateTime` int(11) unsigned NOT NULL,
    PRIMARY KEY (`recordId`),
    KEY `activityId_key` (`activityId`),
    UNIQUE KEY `supporterUserId_activityId_key` (`supporterUserId`, `activityId`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
```

* shell脚本如下

```sh
for ((i=0; i<1000; i++))
do
    index=$(printf "%03d" ${i})
    echo ${index}
    sql=$(sed "s/???/${index}/g" table.sql)
    echo "${sql}"
    mysql -uuser -ppassword -h 127.0.0.1 database -e "${sql}"
done
```

### 方法2：

* table.sql如下

```sql
DROP TABLE IF EXISTS `record_%03d`;
CREATE TABLE `record_%03d` (
    `recordId` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    `supporterUserType` tinyint(1) unsigned NOT NULL,
    `supporterUserId` bigint(20) unsigned NOT NULL,
    `supporterOpenId` varchar(64) NOT NULL,
    `starterUserType` tinyint(1) unsigned NOT NULL,
    `starterUserId` bigint(20) unsigned NOT NULL,
    `starterOpenId` varchar(64) NOT NULL,
    `businessId` tinyint(3) unsigned NOT NULL,
    `activityId` bigint(20) unsigned NOT NULL,
    `commodityId` varchar(64) NOT NULL,
    `supportTime` int(11) unsigned NOT NULL,
    `supportType` tinyint(1) unsigned NOT NULL,
    `recvRedPackTime` int(11) unsigned NOT NULL,
    `redPackId` varchar(64) NOT NULL,
    `lastUpdateTime` int(11) unsigned NOT NULL,
    PRIMARY KEY (`recordId`),
    KEY `activityId_key` (`activityId`),
    UNIQUE KEY `supporterUserId_activityId_key` (`supporterUserId`, `activityId`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;
```

* shell脚本如下

```sh
sqlProto=$(cat table.sql)
for ((i=0; i<1000; i++))
do
    sql=$(printf "${sqlProto}" ${i} ${i})
    echo "${sql}"
    mysql -uuser -ppassword -h 127.0.0.1 database -e "${sql}"
done
```