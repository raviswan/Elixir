defmodule Learningai.Repo.Migrations.AddUserIdToCourses do
  use Ecto.Migration

  def change do
    alter table(:courses) do
        add :user_id, references(:users)
    end

  end
end
