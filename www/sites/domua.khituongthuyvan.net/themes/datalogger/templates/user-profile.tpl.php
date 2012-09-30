<div id="user-profile">
  <h1>
    <?php
    print $user_profile['field_first_name'][0]['#markup'] .' '.
                $user_profile['field_last_name'][0]['#markup']; ?>
  </h1>
  <?php 
    if (isset($user_profile['user_picture']['#markup'])): ?>
    <div id="user-picture">
      <?php 
        print $user_profile['user_picture']['#markup'];         
      ?>
    </div>
  <?php 
    endif; ?>
    
</div>
