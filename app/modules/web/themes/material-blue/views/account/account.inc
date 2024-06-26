<?php
/*
 * sysPass
 *
 * @author nuxsmin
 * @link https://syspass.org
 * @copyright 2012-2022, Rubén Domínguez nuxsmin@$syspass.org
 *
 * This file is part of sysPass.
 *
 * sysPass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sysPass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with sysPass.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @var callable       $_getvar
 * @var ThemeIcons     $icons
 * @var AccountExtData $accountData
 * @var AccountAcl     $accountAcl
 * @var ConfigData     $configData
 */

use SP\Config\ConfigData;
use SP\Core\UI\ThemeIcons;
use SP\DataModel\AccountExtData;
use SP\Mvc\View\Components\SelectItem;
use SP\Services\Account\AccountAcl;

$accountData = $_getvar('accountData');
$accountAcl = $_getvar('accountAcl');
$gotData = $_getvar('gotData', false);
$showLinked = $gotData && count($_getvar('linkedAccounts', [])) > 0;
$showFiles = $gotData && $configData->isFilesEnabled() && $accountAcl->isShowFiles();
$showDetails = $gotData && $accountAcl->isShowDetails();
$showPermissions = $accountAcl->isShowPermission()
    || $_getvar('allowPrivate', false)
    || $_getvar('allowPrivateGroup', false);
$showCustomFields = count($_getvar('customFields', 0)) > 0;
?>

<div class="data-container">
    <div id="title" class="titleNormal">
        <i class="material-icons"><?php echo $_getvar('title')['icon']; ?></i>
        <?php echo $_getvar('title')['name']; ?>
    </div>

    <div class="mdl-tabs mdl-js-tabs mdl-js-ripple-effect">
        <div class="mdl-tabs__tab-bar">
            <a href="#account-panel"
               class="mdl-tabs__tab is-active"><?php echo __('Account'); ?></a>

            <?php if ($showCustomFields): ?>
                <a href="#customfield-panel"
                   class="mdl-tabs__tab"><?php echo __('Custom Fields'); ?></a>
            <?php endif; ?>

            <?php if ($showPermissions): ?>
                <a href="#permission-panel"
                   class="mdl-tabs__tab"><?php echo __('Permissions'); ?></a>
            <?php endif; ?>

            <?php if ($showFiles): ?>
                <a href="#file-panel"
                   class="mdl-tabs__tab"><?php echo __('Files'); ?></a>
            <?php endif; ?>

            <?php if ($showDetails): ?>
                <a href="#detail-panel"
                   class="mdl-tabs__tab"><?php echo __('Details'); ?></a>
            <?php endif; ?>

            <?php if ($showLinked): ?>
                <a href="#linked-panel"
                   class="mdl-tabs__tab"><?php echo __('Links'); ?></a>
            <?php endif; ?>
        </div>

        <form method="post" name="frmaccount" id="frmAccount"
              class="form-action"
              data-onsubmit="account/save"
              data-action-route="<?php echo $_getvar('formRoute') ?: ''; ?>"
              data-item-id="<?php echo $_getvar('accountId') ?: ''; ?>"
              data-hash="">

            <input type="hidden" name="sk" value="<?php echo $sk; ?>">
            <input type="hidden" name="isAjax" value="1">

            <div class="mdl-tabs__panel is-active" id="account-panel">
                <table class="data">
                    <tr>
                        <td class="descField"><?php echo __('Name'); ?></td>
                        <td class="valField">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input id="name" name="name" type="text"
                                       required
                                       class="mdl-textfield__input mdl-color-text--indigo-400"
                                       maxlength="100"
                                       value="<?php echo $gotData
                                           ? htmlspecialchars($accountData->getName(), ENT_QUOTES)
                                           : ''; ?>"
                                    <?php echo $_getvar('readonly'); ?>
                                >
                                <label class="mdl-textfield__label"
                                       for="name"><?php echo __('Account name'); ?></label>
                            </div>
                        </td>
                    </tr>
                    <tr>
                        <td class="descField"><?php echo __('Client'); ?></td>
                        <td class="valField">
                            <div class="lowres-title"><?php echo __('Client'); ?></div>

                            <select id="client_id" name="client_id"
                                    class="select-box"
                                    required <?php echo $_getvar('disabled'); ?>>
                                <option value=""><?php echo __('Select Client'); ?></option>
                                <?php /** @var SelectItem $client */
                                $clients = $_getvar('clients');
                                foreach ($clients as $client): ?>
                                    <option
                                            value="<?php echo $client->getId(); ?>"
                                        <?php echo ($gotData && $client->getId() === $accountData->getClientId())
                                            ? 'selected'
                                            : ''; ?>
                                    >
                                        <?php echo htmlspecialchars($client->getName(), ENT_QUOTES); ?>
                                    </option>
                                <?php endforeach; ?>
                            </select>
                            <?php if ($_getvar('addClientEnabled')): ?>
                                <i class="material-icons btn-action btn-add-select"
                                   title="<?php echo __('New Client'); ?>"
                                   data-action-route="<?php echo $_getvar('addClientRoute'); ?>"
                                   data-item-route="items/clients"
                                   data-item-dst="client_id"
                                   data-item-id="0"
                                   data-onclick="appMgmt/show"><?php echo $icons->getIconAdd()->getIcon(); ?></i>
                            <?php endif; ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="descField"><?php echo __('Category'); ?></td>
                        <td class="valField">
                            <div class="lowres-title"><?php echo __('Category'); ?></div>

                            <select id="category_id" name="category_id"
                                    class="select-box"
                                    required <?php echo $_getvar('disabled'); ?>>
                                <option value=""><?php echo __('Select Category'); ?></option>
                                <?php /** @var SelectItem $category */
                                $categories = $_getvar('categories');
                                foreach ($categories as $category): ?>
                                    <option
                                            value="<?php echo $category->getId(); ?>"
                                        <?php echo ($gotData && $category->getId() === $accountData->getCategoryId())
                                            ? 'selected'
                                            : ''; ?>
                                    >
                                        <?php echo htmlspecialchars($category->getName(), ENT_QUOTES); ?>
                                    </option>
                                <?php endforeach; ?>
                            </select>
                            <?php if ($_getvar('addCategoryEnabled')): ?>
                                <i class="material-icons btn-action btn-add-select"
                                   title="<?php echo __('New Category'); ?>"
                                   data-action-route="<?php echo $_getvar('addCategoryRoute'); ?>"
                                   data-item-route="items/categories"
                                   data-item-dst="category_id"
                                   data-item-id="0"
                                   data-onclick="appMgmt/show"><?php echo $icons->getIconAdd()->getIcon(); ?></i>
                            <?php endif; ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="descField"><?php echo __('URL / IP'); ?></td>
                        <td class="valField">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input id="url" name="url" type="text"
                                       class="mdl-textfield__input mdl-color-text--indigo-400"
                                       maxlength="255"
                                       value="<?php echo $gotData
                                           ? htmlspecialchars($accountData->getUrl(), ENT_QUOTES)
                                           : ''; ?>"
                                    <?php echo $_getvar('readonly'); ?>
                                >
                                <label class="mdl-textfield__label"
                                       for="name"><?php echo __('Access URL or IP'); ?></label>
                            </div>
                        </td>
                    </tr>
                    <tr>
                        <td class="descField"><?php echo __('User'); ?></td>
                        <td class="valField">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input id="login" name="login" type="text"
                                       class="mdl-textfield__input mdl-color-text--indigo-400"
                                       maxlength="50"
                                       value="<?php echo $gotData
                                           ? htmlspecialchars($accountData->getLogin(), ENT_QUOTES)
                                           : ''; ?>"
                                    <?php echo $_getvar('readonly'); ?>
                                >
                                <label class="mdl-textfield__label"
                                       for="name"><?php echo __('Access user'); ?></label>
                            </div>
                        </td>
                    </tr>
                    <?php if (!$accountAcl->isShowPass()): ?>
                        <tr>
                            <td class="descField"><?php echo __('Password'); ?></td>
                            <td class="valField">
                                <div class="lowres-title"><?php echo __('Copy Password to Clipboard'); ?></div>
                                <?php
                                $accountActionsMenu = $_getvar('accountActionsMenu');
                                if ($accountActionsMenu && count($accountActionsMenu) > 0): ?>
                                    <div>
                                        <?php foreach (array_reverse($accountActionsMenu) as $action): ?>
                                            <?php if ($action->getId() == "7"): ?>
                                                <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--accent btn-action <?php echo $action->getClassesAsString(); ?>"
                                                    id="<?php echo $action->getId(); ?>"
                                                    <?php foreach ($action->getData() as $key => $value): echo 'data-', $key, '="', $value, '"'; endforeach; ?>
                                                    <?php foreach ($action->getAttributes() as $key => $value): echo $key, '="', $value, '"'; endforeach; ?>
                                                    title="<?php echo $action->getTitle(); ?>">
                                                    <i class="material-icons"><?php echo $action->getIcon()->getIcon(); ?></i>
                                                    <?php echo $action->getName(); ?>
                                                </button>
                                            <?php endif; ?>
                                        <?php endforeach; ?>
                                    </div>
                                <?php endif; ?>
                            </td>
                        </tr>
                    <?php endif; ?>
                    <?php if ($accountAcl->isShowPass()): ?>
                        <tr>
                            <td class="descField"><?php echo __('Password'); ?></td>
                            <td class="valField">
                                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                    <input id="password" name="password"
                                           type="password" required
                                           class="mdl-textfield__input mdl-color-text--indigo-400 passwordfield__input"
                                           maxlength="255"
                                           autocomplete="off">
                                    <label class="mdl-textfield__label"
                                           for="password"><?php echo __('Password'); ?></label>
                                </div>
                            </td>
                        </tr>
                        <tr>
                            <td class="descField"><?php echo __('Password (repeat)'); ?></td>
                            <td class="valField">
                                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                    <input id="password_repeat"
                                           name="password_repeat"
                                           type="password" required
                                           class="mdl-textfield__input mdl-color-text--indigo-400"
                                           maxlength="255" autocomplete="off">
                                    <label class="mdl-textfield__label"
                                           for="password_repeat"><?php echo __('Password (repeat)'); ?></label>
                                </div>
                            </td>
                        </tr>
                        <?php if ($configData->isAccountExpireEnabled()): ?>
                            <tr>
                                <td class="descField"><?php echo __('Password Expiry Date'); ?></td>
                                <td class="valField">
                                    <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                        <input id="password_date_expire"
                                               name="password_date_expire"
                                               type="date"
                                               class="mdl-textfield__input mdl-color-text--indigo-400 password-datefield__input"
                                               value="<?php echo $_getvar('accountPassDateChange'); ?>"
                                               data-dst-unix="password_date_expire_unix"
                                            <?php echo $_getvar('readonly'); ?>
                                        >
                                        <input type='hidden'
                                               name='password_date_expire_unix'
                                               value=""/>
                                        <label class="mdl-textfield__label"
                                               for="password_date_expire"><?php echo __('Date'); ?></label>
                                    </div>

                                    <i class="material-icons btn-action"
                                       title="<?php echo __('Select date'); ?>">date_range</i>
                                </td>
                            </tr>
                        <?php endif; ?>
                    <?php endif; ?>
                    <tr>
                        <td class="descField"><?php echo __('Notes'); ?></td>
                        <td class="valField">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                        <textarea
                                class="mdl-textfield__input mdl-color-text--indigo-400"
                                rows="3" id="notes"
                                name="notes"
                                maxlength="5000" <?php echo $_getvar('readonly'); ?>><?php echo $gotData
                                ? htmlspecialchars($accountData->getNotes(), ENT_QUOTES) : ''; ?></textarea>
                                <label class="mdl-textfield__label"
                                       for="notes"><?php echo __('Notes about the account'); ?></label>
                            </div>
                    </tr>
                    <tr>
                        <td class="descField"><?php echo __('Tags'); ?></td>
                        <td class="valField">
                            <div class="lowres-title"><?php echo __('Tags'); ?></div>

                            <?php if (!$_getvar('isView')): ?>
                                <select id="tags" name="tags[]"
                                        multiple="multiple"
                                        class="select-box-tags">
                                    <option value=""><?php echo __('Select Tags'); ?></option>
                                    <?php /** @var SelectItem $tag */
                                    foreach ($_getvar('tags') as $tag): ?>
                                        <option value="<?php echo $tag->getId(); ?>"
                                            <?php echo $tag->isSelected() ? 'selected' : ''; ?>>
                                            <?php echo htmlspecialchars($tag->getName(), ENT_QUOTES); ?>
                                        </option>
                                    <?php endforeach; ?>
                                </select>
                                <?php if ($_getvar('addTagEnabled')): ?>
                                    <i class="material-icons btn-action btn-add-select"
                                       title="<?php echo __('New Tag'); ?>"
                                       data-action-route="<?php echo $_getvar('addTagRoute'); ?>"
                                       data-item-route="items/tags"
                                       data-item-dst="tags"
                                       data-item-id="0"
                                       data-onclick="appMgmt/show">
                                        <?php echo $icons->getIconAdd()->getIcon(); ?>
                                    </i>
                                <?php endif; ?>
                                <?php if ($_getvar('copyAction')): ?>
                                    <input type="hidden" name="tags_update"
                                           value="1">
                                <?php endif; ?>
                            <?php else: ?>
                                <div class="tag-list-box">
                                    <div class="tag-list-body">
                                        <div class="tags-list-items">
                                            <?php /** @var SelectItem $tag */
                                            foreach ($_getvar('tags') as $tag): ?>
                                                <?php if ($tag->isSelected()): ?>
                                                    <span class="tag"><?php echo htmlspecialchars($tag->getName(), ENT_QUOTES); ?></span>
                                                <?php endif; ?>
                                            <?php endforeach; ?>
                                        </div>
                                    </div>
                                </div>
                            <?php endif; ?>
                        </td>
                    </tr>

                    <?php if (!$showLinked): ?>
                        <tr>
                            <td class="descField"><?php echo __('Linked Account'); ?></td>
                            <td class="valField">
                                <div class="lowres-title"><?php echo __('Linked Account'); ?></div>

                                <select id="parent_account_id"
                                        name="parent_account_id"
                                        class="select-box select-box-deselect" <?php echo $_getvar('disabled'); ?>
                                        data-sk="<?php echo $_getvar('sk'); ?>"
                                        data-action-route="items/accountsUser"
                                        data-item-id="<?php echo $gotData ? $_getvar('accountId') : ''; ?>"
                                        data-selected-id="<?php echo $gotData ? $accountData->getParentId() : ''; ?>">
                                    <option value=""><?php echo __('Select Account'); ?></option>
                                </select>
                            </td>
                        </tr>
                    <?php endif; ?>

                    <?php if ($accountAcl->isShowHistory()
                        && count($_getvar('historyData', [])) > 0): ?>
                        <tr>
                            <td class="descField"><?php echo __('History'); ?></td>
                            <td class="valField">
                                <div class="lowres-title"><?php echo __('History'); ?></div>

                                <select id="history_id" name="history_id"
                                        class="select-box"
                                        data-action-route="account/viewHistory"
                                        data-onchange="account/viewHistory">
                                    <option value=""><?php echo __('Select date'); ?></option>
                                    <?php /** @var SelectItem $history */
                                    foreach ($_getvar('historyData') as $history): ?>
                                        <option
                                                value="<?php echo $history->getId(); ?>">
                                            <?php echo htmlspecialchars($history->getName(), ENT_QUOTES); ?>
                                        </option>
                                    <?php endforeach; ?>
                                </select>
                            </td>
                        </tr>
                    <?php endif; ?>

                    <?php if ($_getvar('editAction')
                        && $_getvar('isModified', false)
                        && $accountData->getUserEditName()): ?>
                        <tr>
                            <td class="descField"><?php echo __('Last Modification'); ?></td>
                            <td class="valField"><?php printf('%s (%s)',
                                    $accountData->getDateEdit(),
                                    htmlspecialchars($accountData->getUserEditName(), ENT_QUOTES)); ?>
                            </td>
                        </tr>
                    <?php endif; ?>

                    <?php if ($_getvar('publicLinkShow', false) === true
                        && $_getvar('publicLinkUrl') !== null): ?>
                        <tr>
                            <td class="descField"><?php echo __('Public Link'); ?></td>
                            <td class="valField">
                                <div class="lowres-title"><?php echo __('Public Link'); ?></div>

                                <a href="<?php echo $_getvar('publicLinkUrl'); ?>"
                                   target="_blank"
                                   title="<?php echo __('Public Link'); ?>">
                                    <i class="material-icons"><?php echo $icons->getIconPublicLink()->getIcon(); ?></i>
                                </a>
                            </td>
                        </tr>
                    <?php endif; ?>

                    <?php if ($_getvar('accountId')): ?>
                        <tr>
                            <td class="descField"><?php echo __('Direct Link'); ?></td>
                            <td class="valField">
                                <div class="lowres-title"><?php echo __('Direct Link'); ?></div>

                                <a href="<?php echo $_getvar('deepLink'); ?>"
                                   target="_blank"
                                   title="<?php echo __('Direct Link'); ?>">
                                    <i class="material-icons"><?php echo $icons->getIconPublicLink()->getIcon(); ?></i>
                                </a>
                            </td>
                        </tr>
                    <?php endif; ?>
                </table>
            </div>

            <div class="mdl-tabs__panel" id="customfield-panel">
                <?php if ($showCustomFields): ?>
                    <div id="data-customfields">
                        <table class="data">
                            <?php include $this->includeTemplate('aux-customfields', 'common'); ?>
                        </table>
                    </div>
                <?php endif; ?>
            </div>

            <div class="mdl-tabs__panel" id="permission-panel">
                <?php if ($showPermissions):
                    include $this->includeTemplate('account-permissions');
                endif; ?>
            </div>
        </form>

        <div class="mdl-tabs__panel" id="file-panel">
            <?php if ($showFiles) :
                include $this->includeTemplate('files');
            endif; ?>
        </div>

        <div class="mdl-tabs__panel" id="detail-panel">
            <?php if ($showDetails):
                include $this->includeTemplate('details');
            endif; ?>
        </div>

        <div class="mdl-tabs__panel" id="linked-panel">
            <?php if ($showLinked):
                include $this->includeTemplate('linkedAccounts');
            endif; ?>
        </div>
    </div>

    <?php include $this->includeTemplate('actions'); ?>
</div>